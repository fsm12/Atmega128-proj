#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define DT PD7		// A
#define CLK PD6		// B
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)
volatile unsigned char flag;

int cnt = 0;
double dist;

ISR(USART1_RX_vect)
{
   flag=UDR1;
}

void init()
{
   DDRA=0xff;
   UCSR1A=0x00;
   UCSR1B=0x98;
   UCSR1C=0x06;
   UBRR1H=0;
   UBRR1L=8;
   sei();
}

void Putch(char data){
   while(!(UCSR1A&0x20));
   UDR1=data;
}

void Putstr(char *pStr){
   while(*pStr)
      Putch(*pStr++);
}

int main(void){
   DDRD = 0x1;
   PORTD = 0x0;
   
   int curDT;  // 현재 A 펄스값
   int curCLK;  // 현재 B 펄스값
   int preDT = (PIND&(1<<DT));  // 전 A 펄스값
   int preCLK = (PIND&(1<CLK));  // 전 B 펄스값
   init();
   char strcnt[10]; 

   while(1){
      	if(flag=='B'){   // 스타트
         	while(1){
            	if(flag=='A'){   // 리셋
               		cnt=0;
               		break;
            	}
            	curDT = !(PIND&(1<<DT));
            	curCLK = !(PIND&(1<<CLK));
     
            	if((curDT != preDT) || (curCLK != preCLK)){  // 클락 change
            		if(curDT != preCLK)
                		cnt--;
               		else
                		cnt++;
            
            	dist = 2.625 * cnt; // 거리 = (원주 / 80) * cnt 
            	if(dist < 0)		
            		dist = dist * (-1);
            	sprintf(strcnt, "%0.3f mm", dist);
            	Putstr(strcnt);
            	Putstr("\n");
         	}
         	preDT = curDT;
         	preCLK = curCLK; 
        }
      }
   }
}
