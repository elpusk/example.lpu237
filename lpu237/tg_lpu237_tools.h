#pragma once

/*!
*   code example is https://github.com/elpusk/example.lpu237
*	2022.11.	- coding starting.......
*	2022.11.24 - release v1.0 .  add LPU237_tools_msr_set_default().
*
*/
#include <Windows.h>

/*!
*	constant definition.
*/
#define	LPU237_TOOLS_SIZE_ID				16			//device ID is 16 bytes.
#define	LPU237_TOOLS_SIZE_NAME				16			//device Name is 16 bytes.
#define	LPU237_TOOLS_SIZE_VERSION			4			//firmware version is 4 bytes.

/*!
*	return value definition.
*/
#define	LPU237_TOOLS_RESULT_SUCCESS		0		//! processing success.
#define	LPU237_TOOLS_RESULT_ERROR			0xFFFFFFFF	//! processing error.( maybe system or communication error ); (-1)
#define	LPU237_TOOLS_RESULT_CANCEL			0xFFFFFFFE	//! processing is canceled by another reqest.(-2)
//#define	LPU237_TOOLS_RESULT_TIMEOUT		0xFFFFFFFC	//! processing is timeout.(-4)....... Don't use
#define	LPU237_TOOLS_RESULT_NO_MSR			0xFFFFFFFb	//! processing not found MSR .(-5)

/*!
*	windows' message wparam value
*/
#define	LPU237_TOOLS_WPARAM_COMPLETE		0	//firmware update complete.
#define	LPU237_TOOLS_WPARAM_SUCCESS		0	//firmware update complete.
#define	LPU237_TOOLS_WPARAM_FOUND_BL		1	//found bootloader.
#define	LPU237_TOOLS_WPARAM_SECTOR_ERASE	2
#define	LPU237_TOOLS_WPARAM_SECTOR_WRITE	3

#define	LPU237_TOOLS_WPARAM_ERROR			0xFFFF


/*!
*	the callback function type.
*	this type will be used in LPU237_tools_msr_update()
*	
*	parameters
*		1'st - user defined data.
*		2'nd - current processing result : LPU237_TOOLS_RESULT_x
*		3'th - LPU237_TOOLS_WPARAM_x.
*/
typedef	DWORD (WINAPI *type_lpu237_tools_callback)(void*,DWORD,DWORD);

/*!
*	the callback function type.
*	this type will be used in LPU237_tools_msr_start_get_setting()
*
*	parameters
*		1'st - user defined data.
*		2'nd - current processing result : LPU237_TOOLS_RESULT_x
*		3'th - currnent step index : zero-base index.
*		4'th - the total step : step index >= 0 and step index < this value
*/
typedef	DWORD(WINAPI* type_lpu237_tools_callback_get_parameter)(void*, DWORD, DWORD, DWORD);

/*!
*	the callback function type.
*	this type will be used in LPU237_tools_msr_start_set_setting()
*
*	parameters
*		1'st - user defined data.
*		2'nd - current processing result : LPU237_TOOLS_RESULT_x
*		3'th - currnent step index : zero-base index.
*		4'th - the total step : step index >= 0 and step index < this value
*		5'th - reserved value 
*/
typedef	DWORD(WINAPI* type_lpu237_tools_callback_set_parameter)(void*, DWORD, DWORD, DWORD, DWORD);

/*!
* function
*	initial lpu237 internal data.
*
* parameters
*
* return
*  	LPU237_TOOLS_RESULT_SUCCESS : only.
*
*/
DWORD WINAPI LPU237_tools_on();

/*!
* function
*	Deinitial lpu237 internal data.
*
* parameters
*
* return
*  	LPU237_TOOLS_RESULT_SUCCESS : only.
*
*/
DWORD WINAPI LPU237_tools_off();

/*!
* function
*	get connected device list.( unicode version )
*
* parameters
*	ssDevPaths : [in/out] Multi string of devices paths. 
*					this value can be NULL(0).
*
*	return
*		if ssDevPaths = NULL, the number of character.(including NULL). one character size = 2 bytes
*		else the number of connected lpu237 device.
*/
DWORD WINAPI LPU237_tools_get_list_w( WCHAR *ssDevPaths );

/*!
* function 
*	open device.( unicode version )
*
* parameters
*	sDevPath : [in] device path - unicode type zero-string
*
* return 
*	if success, return device handle.
*	else return INVALID_HANDLE_VALUE
*/
HANDLE WINAPI LPU237_tools_open_w( CONST WCHAR *sDevPath );

/*!
* function
*	close lpu237 device.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*
* return
*	if success, return LPU237_TOOLS_RESULT_SUCCESS
*	else return LPU237_TOOLS_RESULT_ERROR
*/
DWORD WINAPI LPU237_tools_close( HANDLE hDev );

/*!
* function
*	is supported magnetic card reading.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	pc_support : [in/out] 1 - be supported, 0 -not be suported
*
* return
*	if success, return LPU237_TOOLS_RESULT_SUCCESS
*	else return LPU237_TOOLS_RESULT_ERROR
*/
DWORD WINAPI LPU237_tools_msr_is_support_msr(HANDLE hDev, BYTE* pc_support);

/*!
* function
*	is supported ibutton reading.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	pc_support : [in/out] 1 - be supported, 0 -not be suported
*
* return
*	if success, return LPU237_TOOLS_RESULT_SUCCESS
*	else return LPU237_TOOLS_RESULT_ERROR
*/
DWORD WINAPI LPU237_tools_msr_is_support_ibutton(HANDLE hDev, BYTE* pc_support);

/*!
* function
*	get device unique ID.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	sId : [in/out] A pointer to the buffer that save the device ID.( ID is 16 bytes )
*			this value can be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the size of ID.[unit byte]
*/
DWORD WINAPI LPU237_tools_msr_get_id(HANDLE hDev, BYTE* sId);


/*!
* function
*	start load parameter from device.( unicode version )
*
* parameters
*	sId : [in] the device ID.( ID is 16 bytes )
*	cb : [in] callback function for get system paramter.
*	pUser : [in] user data pointer for calling cb().
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR.
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_start_get_setting(const BYTE* sId, type_lpu237_tools_callback_get_parameter cb, void* pUser);

/*!
* function
*	start save parameter to device.( unicode version )
*
* parameters
*	sId : [in] the device ID.( ID is 16 bytes )
*	cb : [in] callback function for set system paramter.
*	pUser : [in] user data pointer for calling cb().
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR.
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_start_set_setting(const BYTE* sId, type_lpu237_tools_callback_set_parameter cb, void* pUser);

/*!
* function
*	start load parameter from device.( unicode version ). except combination parameter
*
* parameters
*	sId : [in] the device ID.( ID is 16 bytes )
*	cb : [in] callback function for get system paramter.
*	pUser : [in] user data pointer for calling cb().
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR.
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_start_get_setting_except_combination(const BYTE* sId, type_lpu237_tools_callback_get_parameter cb, void* pUser);


/*!
* function
*	start save parameter to device.( unicode version ) except combination parameter
*
* parameters
*	sId : [in] the device ID.( ID is 16 bytes )
*	cb : [in] callback function for set system paramter.
*	pUser : [in] user data pointer for calling cb().
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR.
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_start_set_setting_except_combination(const BYTE* sId, type_lpu237_tools_callback_set_parameter cb, void* pUser);

/*!
* function
*	Don't use this function.
*	save the current lpu237 device setting.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*
* return
*	if success, return LPU237_TOOLS_RESULT_SUCCESS
*	else return LPU237_TOOLS_RESULT_ERROR
*/
DWORD WINAPI LPU237_tools_msr_save_setting( HANDLE hDev );

/*!
* function
*	Don't use this function.
*	resetting  lpu237 device with saved setting.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*
* return
*	if success, return LPU237_TOOLS_RESULT_SUCCESS
*	else return LPU237_TOOLS_RESULT_ERROR
*/
DWORD WINAPI LPU237_tools_msr_recover_setting( HANDLE hDev );

/*!
* function
*	get device internal name.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	sName : [in/out] A pointer to the buffer that save the device name.
*			this value can be NULL(0).
*
* return 
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the size of internal name.[unit byte]
*/
DWORD WINAPI LPU237_tools_msr_get_name( HANDLE hDev, BYTE *sName );


#define	LPU237_TOOLS_INF_USBKB		0	//system interface is USB keyboard.
#define	LPU237_TOOLS_INF_USBHID		1	//system interface is USB MSR(generic HID interface).
#define	LPU237_TOOLS_INF_UART		10	//system interface is uart.
/*!
* function
*	get actived interfafce and valied interfaces
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	interface : [in/out] A pointer to the buffer that save the interface number .each byte contains LPU237_TOOLS_INF_x data.
*			this value can be NULL(0). 1'st byte - active interface number, from 2,nd the list of valied interface.
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the number of interface +1 
*/
DWORD WINAPI LPU237_tools_msr_get_active_and_valied_interface(HANDLE hDev, BYTE* s_inteface);

/*!
* function
*	set active interfafce
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	c_interface : [in] active interface. LPU237_TOOLS_INF_x data.
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_interface(HANDLE hDev, BYTE c_inteface);

/*!
* function
*	set active interfafce to device.(RAM) and be saved.(Flash memory)
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	pc_interface : [in/out] in - active interface, out - deactived interface. LPU237_TOOLS_INF_x data.
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_interface_to_device_and_apply(HANDLE hDev, BYTE* pc_inteface);


/*!
* function
*	get buzzer status.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	pc_on : [in/out] A pointer to unsigned char buffer. buzzer on -> 1, buzzer off -> 0.
*			this value cannot be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_get_buzzer(HANDLE hDev, BYTE* pc_on);

/*!
* function
*	set buzzer status.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	c_on : [in] unsigned char buffer. buzzer on -> 1, buzzer off -> 0.
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_buzzer(HANDLE hDev, BYTE c_on);

#define	LPU237_TOOLS_LANG_USA_ENGLISH	0
#define	LPU237_TOOLS_LANG_SPANISH		1
#define	LPU237_TOOLS_LANG_DANISH		2
#define	LPU237_TOOLS_LANG_FRENCH		3
#define	LPU237_TOOLS_LANG_GERMAN		4
#define	LPU237_TOOLS_LANG_ITALIAN		5
#define	LPU237_TOOLS_LANG_NORWEGIAN		6
#define	LPU237_TOOLS_LANG_SWEDISH		7
#define	LPU237_TOOLS_LANG_UK_ENGLISH	8
#define	LPU237_TOOLS_LANG_ISRAEL		9
#define	LPU237_TOOLS_LANG_TURKIYE		10
/*!
* function
*	get language.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	pc_lang : [in/out] A pointer to unsigned char buffer. language index(LPU237_TOOLS_LANG_x)
*			this value cannot be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_get_language(HANDLE hDev, BYTE* pc_lang);

/*!
* function
*	set language.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	c_lang : [in] unsigned char buffer. language index(LPU237_TOOLS_LANG_x)
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_language(HANDLE hDev, BYTE c_lang);

/*!
* function
*	get track status.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	s_status_3_byte : [in/out] A pointer to unsigned char buffer.
*			each track status , size is 3 bytes. index0 - iso1, index1 - iso2 and index2 - iso3
*			0 : disable, 1 : enable
*			this value cannot be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_get_track_status(HANDLE hDev, BYTE* s_status_3_byte);

/*!
* function
*	set track status.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	s_status_3_byte : [in] A pointer to unsigned char buffer.
*			each track status , size is 3 bytes. index0 - iso1, index1 - iso2 and index2 - iso3
*			0 : disable, 1 : enable
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_track_status(HANDLE hDev, const BYTE* s_status_3_byte);

/*!
* function
*	get private pre/postfix of msr
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	dw_track_zero_base : [in] track number , 0~2
*	b_prefix : [in] 1 - prefix, 0 - postfix
*	s_tag : [in/out] A pointer to the buffer that save the tag.
*			this value can be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the size of s_tag (unit byte)
*/
DWORD WINAPI LPU237_tools_msr_get_private_tag(HANDLE hDev, DWORD dw_track_zero_base, BYTE b_prefix, BYTE* s_tag);

/*!
* function
*	set private pre/postfix of msr
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	dw_track_zero_base : [in] track number , 0~2
*	b_prefix : [in] 1 - prefix, 0 - postfix
*	s_tag : [in] A pointer to the buffer that save the tag.
*	dw_tag : the size of s_tag
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_private_tag(HANDLE hDev, DWORD dw_track_zero_base, BYTE b_prefix, const BYTE* s_tag, DWORD dw_tag);

#define	LPU237_TOOLS_IBUTTON_MODE_NONE		0
#define	LPU237_TOOLS_IBUTTON_MODE_ZEROS		1
#define	LPU237_TOOLS_IBUTTON_MODE_F12		2
#define	LPU237_TOOLS_IBUTTON_MODE_ZEROS7	3
#define	LPU237_TOOLS_IBUTTON_MODE_ADDMIT	4
/*!
* function
*	get i-button mode.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	pc_type : [in/out] A pointer to unsigned char buffer. ibutton mode,(LPU237_TOOLS_IBUTTON_MODE_X)
*			this value cannot be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/

DWORD WINAPI LPU237_tools_msr_get_ibutton_mode(HANDLE hDev, BYTE* pc_mode);

/*!
* function
*	set i-button mode.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	c_mode : [in] A pointer to unsigned char buffer. ibutton mode,(LPU237_TOOLS_IBUTTON_MODE_X)
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/

DWORD WINAPI LPU237_tools_msr_set_ibutton_mode(HANDLE hDev, BYTE c_mode);

/*!
* function
*	get private pre/postfix of i button
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	b_remove : [in] 1 - remove tag, 0 - contact tag
*	b_prefix : [in] 1 - prefix, 0 - postfix
*	s_tag : [in/out] A pointer to the buffer that save the tag.
*			this value can be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the size of s_tag (unit byte)
*/
DWORD WINAPI LPU237_tools_msr_get_ibutton_tag(HANDLE hDev, BYTE b_remove, BYTE b_prefix, BYTE* s_tag);

/*!
* function
*	set private pre/postfix of i button
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	b_remove : [in] 1 - remove tag, 0 - contact tag
*	b_prefix : [in] 1 - prefix, 0 - postfix
*	s_tag : [in] A pointer to the buffer that save the tag.
*	dw_tag : the size of s_tag
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_ibutton_tag(HANDLE hDev, BYTE b_remove, BYTE b_prefix, const BYTE* s_tag, DWORD dw_tag);

/*!
* function
*	get remove-indication tag of i button
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	s_tag : [in/out] A pointer to the buffer that save the tag.
*			this value can be NULL(0).
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the size of s_tag (unit byte)
*/
DWORD WINAPI LPU237_tools_msr_get_ibutton_remove_indication_tag(HANDLE hDev, BYTE* s_tag);

/*!
* function
*	set remove-indication tag of i button
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	s_tag : [in] A pointer to the buffer that save the tag.
*	dw_tag : the size of s_tag
* 
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_ibutton_remove_indication_tag(HANDLE hDev, const BYTE* s_tag, DWORD dw_tag);

/*!
* function
*	set device parameter to default
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*
* return
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else LPU237_TOOLS_RESULT_SUCCESS
*/
DWORD WINAPI LPU237_tools_msr_set_default(HANDLE hDev);


/*!
* function
*	get device firmware version.
*
* parameters
*	hDev : [in] device handle( return value of LPU237_tools_open() )
*	sName : [in/out] A pointer to the buffer that save the device firmware version.( version 4 bytes )
*			this value can be NULL(0).
*
* return 
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else the size of version.[unit byte]
*/
DWORD WINAPI LPU237_tools_msr_get_version( HANDLE hDev, BYTE *sVersion );

/*!
* function
*	get major number from firmware version.
*
* parameters
*	sVersion : [in] device firmware version( return value of LPU237_tools_msr_get_version() ).
*			this value can be NULL(0).
*
* return 
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else major version number.
*/
DWORD WINAPI LPU237_tools_msr_get_version_major( const BYTE *sVersion );

/*!
* function
*	get minor number from firmware version.
*
* parameters
*	sVersion : [in] device firmware version( return value of LPU237_tools_msr_get_version() ).
*			this value can be NULL(0).
*
* return 
* 	if error, return LPU237_TOOLS_RESULT_ERROR
*	else minor version number.
*/
DWORD WINAPI LPU237_tools_msr_get_version_minor( const BYTE *sVersion );

/*!
* function
*	stop operation of LPU237_tools_msr_update_x.
*
* parameters
*
* return
*	if success, return LPU237_TOOLS_RESULT_SUCCESS
*	else return LPU237_TOOLS_RESULT_ERROR
*
*/
DWORD WINAPI LPU237_tools_msr_cancel();
