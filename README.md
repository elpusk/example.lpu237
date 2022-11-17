# example.lpu237
lpu237 device 사용 방법

## tools - vs2019, MFC
- target : windows10
- description : 고객 요청으로 lpu237를 사용하는 방법에 대한 sample code 제작.
- prefix/postfix tag 형식에 관한 설명은 https://blog.naver.com/elpusk/221987287359  의 "tag 형식" 부분 참고.
- 모든 lpu237 하위 타입은 USB keyboard, USB HID interface 는 지원].
- 현재 모든 하위 타입에서 소프트웨어적으로 UART interface 가 지원 되는 알 수 있는 방법 없음.(c,d,e type 만 알 수 있음.)
- 소프트웨어적 방법으로, 프로그램 실행 전에, ibutton 이 연결 또는 제거 상태 인지 구분 불가능. 프로그램 실행 후, 이벤트가 발생하여 ibutton 값을 얻은 후 부터 식별 가능. 
- MSR test 하기 위해서는 OPOS CCO 설치 필요.


## tp_lpu237 project
- 변경내용
  - _exm.h : lpu237 folder로 이동
  - _exm_mgmt_lpu237.h : lpu237 folder로 이동
  - KBConst.h : lpu237 folder로 이동
  - oposmsr.h : lpu237 folder에 추가
  - oposmsr.cpp : lpu237 folder에 추가
  - tg_lpu237_ibutton.dll 추가.
  - tg_lpu237_ibutton.h : lpu237 folder에 추가
  - cdll_lpu237_ibutton.h : lpu237 folder에 추가
  - OPOS 를 이용한 MSR reading test 기능.
