#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define RS PD5
#define RW PD6
#define E PD7

char *string[] = {"Stop watch", "00:00:00"}; // 초기 출력 값
int state = 0; // 상태 변수
int time = 0; // 타임 변수
int main(void){
	
	// 스위치 입력 포트
	DDRF = 0X00;
	PORTF = 0X03;
	
	int r, c; // LCD 두 줄을 순회하기 위한 변수
	
	LCD_init();
	while (1){
		for(r=0; r<2; r++){
			for(c=0; c<16; c++)
			if(string[r][c] == '\0'){
				if(r==0) LCD_command(0XC8); // 출력 위치 결정
				break;
			}
			else LCD_data_write(string[r][c]);
		}
		clock(); // 타임 설정
		// STOP, START SWITCH
		if(!(PINF&0x01)) state=state==1 ? 0 : 1;
		
		// RESET SWITCH
		if(!(PINF&0X02)) { LCD_init(); clock_init(); }
		
		// START -> Time 증가
		if(state) time++;
		_delay_ms(10);
	}
	return 0;
}

// E 신호 스트로브 생성
void gen_E_strobe(void){
	volatile int i;
	
	PORTD |= 1<<E;
	for(i=0; i<10; i++);
	PORTD &= ~(1<<E);
}

// 동작 가능 상태
void wait_BusyFlag(void){
	volatile int i;
	unsigned char bf;
	
	DDRA = 0X0;
	PORTD = (PORTD & ~(1<<RS)) | 1<<RW;
	do {
		PORTD |= 1<<E;
		for(i=0; i<10; i++);
		bf = PINA & 1<<PC7;
		PORTD &= ~(1<<E);
	} while(bf);
}

// 동작 명령
void LCD_command(unsigned char data){
	wait_BusyFlag();
	DDRA = 0xFF;
	PORTA = data;
	PORTD &= ~(1<<RS | 1<<RW);
	gen_E_strobe();
}

// 문자 출력
void LCD_data_write(unsigned char data){
	wait_BusyFlag();
	DDRA = 0XFF;
	PORTA = data;
	PORTD = (PORTD | 1<<RS) & ~(1<<RW);
	gen_E_strobe();
}

// LCD 초기화
void LCD_init(void){
	DDRD |= 1<<RS | 1<<RW | 1<<E;
	PORTD &= ~(1<<RS | 1<<E | 1<<RW);
	LCD_command(0X3C);
	LCD_command(0X02);
	LCD_command(0X01);
	LCD_command(0X06);
	LCD_command(0X0F);
}

// 시간 설정
void clock(void){
	string[1][0] = time / 60000 % 6 + 48;
	string[1][1] = time / 6000 % 10 + 48;
	string[1][3] = time / 1000 % 6 + 48;
	string[1][4] = time / 100 % 10 + 48;
	string[1][6] = time / 10 % 10 + 48;
	string[1][7] = time % 10 + 48;
}

// Clock 초기화
void clock_init(void){
	time = 0;
}
