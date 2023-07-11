# <div align="center">distance_measurement</div>
<div align="center">ATmega128를 이용한 거리측정 프로젝트</div>
<div align="center">[ 2020.11.06 ~ 2020.11.27 ]</div>

## 📖 과제 요구사항
1. **과제** : 평평한 바닥에서 출발선부터 수동으로 이동하는 물체의 이동 거리 계산
2. **점수** : 5개 포인트에 대한 연속적인 거리 오차의 합
3. **승리** : 오차를 최소로 하는 팀
4. **대표 상품**
<img src="https://github.com/fsm12/distance_measurement/assets/74345771/249bc0f9-a29c-4e00-ad0c-d31d05e4648f" width=120 height=150>

5. **조건**
 - 센서를 2개 이내 사용
 - AVR128 보드 사용
 - 블루투스 사용
 - 휴대폰 앱에 이동 거리 출력(메뉴는 reset, start)
 - mm 단위 출력
 - 이동하는 물체와 최소 50cm 떨어져 간접적으로 이동을 시켜야 함.
 - 기회는 한번
6. **문제**
 - 직선 문제(연속) 1.0m, 1.5m, 3.0m, 4.5m
 - 곡선 문제(연속) 1.0m, 2.0m, 3.0m
 - 임의 모형(연속) 1.0m, 2.0m, 3.0m


## 🤔 접근
팀원들과 회의를 한 결과, 거리를 측정하기 위해서는

1. 빛이나 초음파를 쏘아서 반사되는 시간을 고려하는 방법
2. 상대적으로 이동한 좌표 측정이 가능하도록 하는 방법(==광마우스의 원리)
3. 바퀴의 회전 속도(각속도)나 움직인 각도를 측정하는 방법

등을 이용하면 될 것이라 의견이 나왔고, 이에 따라 ‘수/발광 센서’, ‘초음파 센서’, ‘6축 가속도 센서(MPU 6050)’, ‘로터리 엔코더 센서’가 언급되었습니다.

ⓑ의 경우는 광센서에서 반사되는 값의 이미지 처리를 위해 DSP 칩이 따로 필요하다는 사실을 알게 되어 제외

ⓒ의 한 방법으로 가속도 센서 모듈인 MPU 6050의 경우, 3개의 x, y, z축 가속도 센서와 2개의 포지션 센서가 있으므로 이를 이용하면 더 정밀하게 측정이 가능할 것이라는 생각을 했지만, 계산할 때 가속도 값을 두 번 적분해야 거리가 나오므로 적분상수로 인한 오차값이 커질 것으로 예상하여 제외

ⓒ의 다른 방법으로 ‘로터리 엔코더 센서’의 경우, 두 펄스열을 이용한 방법이기 때문에 복잡한 계산이 필요하지 않아 코드 길이를 줄일 수 있고 회로 구성도 단순화할 수 있으며 오차 또한 많이 생기지 않아 이 센서를 선택하였습니다.


## 🔧 사용부품
<img src="https://github.com/fsm12/distance_measurement/assets/74345771/5853053e-8be1-49f2-beee-2037d8f7e40b" width=380 height=320>

-  ATmega128 보드 : JMOD-128-1
-  블루투스 : JMOD-BT-1
-  로터리 엔코더 모듈 : TS0194

## 🔨 기기 사진
![image](https://github.com/fsm12/distance_measurement/assets/74345771/2dede157-1bd6-405c-b50d-41c323483687)

## 📝 실행 결과
<img src="https://github.com/fsm12/distance_measurement/assets/74345771/8e6d6d92-e734-4b68-94e1-e674e9b281af" width=200 height=350>
<img src="https://github.com/fsm12/distance_measurement/assets/74345771/84733244-5558-40b3-82f4-5b8366fb2421" width=520 height=200>

타학생들보다 우수한 기록을 낼 수 있었습니다.

## 😁 Developer
|팀장|팀원|팀원|
|---|---|---|
|<div align="center">[박소미](https://github.com/fsm12)</div>|<div align="center">[정수진](https://github.com/sujin13)</div>|이지수|
