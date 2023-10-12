# example.lpu237
lpu237 device 사용 방법

## tools - vs2019, MFC
- target : windows10
- description : 고객 요청으로 lpu237를 사용하는 방법에 대한 sample code 제작.
- prefix/postfix tag 형식에 관한 설명은 https://blog.naver.com/elpusk/221987287359  의 "tag 형식" 부분 참고.
- 모든 lpu237 하위 타입은 USB keyboard, USB HID interface 는 지원.
- 현재 모든 하위 타입에서 소프트웨어적으로 UART interface 가 지원 되는 알 수 있는 방법 없음.(c,d,e type 만 알 수 있음.)
- 소프트웨어적 방법으로, 프로그램 실행 전에, ibutton 이 연결 또는 제거 상태 인지 구분 불가능. 프로그램 실행 후, 이벤트가 발생하여 ibutton 값을 얻은 후 부터 식별 가능. 
- MSR test 하기 위해서는 OPOS CCO 설치 필요.
- 프로그램 실행 시키기 위해서는 [mapper full version](https://github.com/elpusk/public.lpu237.software/tree/main/full/x86) 설치. 필요.


## tp_lpu237 project
- 중요 검토 사항.
  - ibutton test 를 위해서는 interface가 USB_HID로 설정되어야 하기 위해, 편의를 목적으로 
  - c_dlg_test_water_lock::OnInitDialog() 에서  mgmt.set_active_port_type_to_device_but_not_apply_by_string(L"USB_HID") 를 호출해서, 강제로 USB_HID 모드로 변경 하고
  - c_dlg_test_water_lock 닫을 때  mgmt.set_active_port_type_to_device_but_not_apply_by_string(m_s_old_interface) 를 호출해서, interface mode 복구 한다.
  - 이러한 방법은 마이컴 flash 쓰기를 발생 시켜, 마이컴 flash 쓰기 수명을 단축한다. 따라서 사용자 application 의 목적에 따라 고려하여
  - 이 편의 기능을 사용 할 것인지 말 것인지 검토해야 한다.
  - 프로그램에서 사용 중인 dll( tg_lpu237_tools.dll, tg_lpu237_ibutton.dll 그리고 tg_rom.dll ) 가 업데이트 되었을 때, mapper 와 함께 배포 인스톨된 것들을 먼저 사용하게 설정하여,
  - 다른 버전의 dll 이 다수 설치되어 발생하는 dll 지옥을 막아보는 것이 필요한지 검토 필요.

- 변경내용
  - 2023.10.12
    - tp_lpu237.exe v1.3
    - tp_lpu237.exe 에서 사용하는 tg_lpu237_tools.dll 가 v4.1 로 업데이트 되면서, i-button 전송 범위 설정 기능이 추가되어, 이 기능(i-button range) 사용 예제를 tp_lpu237.exe 에 추가해서, v1.3 으로 업데이트.(1.2는 설명이 없는데 lpu238 장비 지원)
    - i-button range 기능을 사용하기 위해서는, callisto v3.23, ganymede v5.22 또는 europa v1.1 펨웨어가 탑재된, i-button 읽기 기능을 가진 장비가 있어야 함.
    - tg_lpu237_tools.dll v4.1 에 LPU237_tools_msr_is_support_ibutton_range() 함수 추가 :  i-button range 기능 지원 여부 확인을 위해. 단 i-button 기능 지원 여부는 LPU237_tools_msr_is_support_ibutton() 를 계속 사용해야 함.
    - tg_lpu237_tools.dll v4.1 에 LPU237_tools_msr_get_ibutton_start_zero_base_offset_of_range() 함수 추가 :  i-button range 기능에서 현재 range 시작 offset 얻기 위해.
    - tg_lpu237_tools.dll v4.1 에 LPU237_tools_msr_get_ibutton_end_zero_base_offset_of_range() 함수 추가 :  i-button range 기능에서 현재 range 종료 offset 얻기 위해.
    - tg_lpu237_tools.dll v4.1 에 LPU237_tools_msr_set_ibutton_start_zero_base_offset_of_range() 함수 추가 :  i-button range 기능에서 range 시작 offset 설정 위해.
    - tg_lpu237_tools.dll v4.1 에 LPU237_tools_msr_set_ibutton_end_zero_base_offset_of_range() 함수 추가 :  i-button range 기능에서 range 종료 offset 설정 위해.
    
  - 2023.09.01
    - tp_lpu237.exe v1.1
    - tg_lpu237_tools.dll 테스트 편리성을 위해, tp_lpu237.exe 와 같은 폴더에 tp_lpu237.ini 가 존재하고, "ini" section 에 key name "components_path" 의 value 가 존재하면, 그 값에 정의된 path 애서  tg_lpu237_tools.dll를 로드함.
```
; tp_lpu237.ini  예제
; 현제 폴더에서 tg_lpu237_tools.dll 를 로드.
[ini]
components_path = "."
```
  
  