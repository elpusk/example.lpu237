#pragma once

#include <Windows.h>

#include <list>
#include <string>
#include <vector>
#include <memory>

#include "tg_lpu237_tools.h"

class cdll_lpu237_tools
{
public:
	typedef std::vector<unsigned char> type_v_id;
	typedef std::list<std::wstring> type_list_wstring;
	typedef	std::shared_ptr<cdll_lpu237_tools>	type_ptr;
	typedef	std::pair<bool, bool> type_pair_result_enable;
	typedef	std::pair<bool, std::wstring> type_pair_result_string;
	typedef	std::vector<unsigned char>	type_v_tag;

private:
	typedef	DWORD(__stdcall* _type_LPU237_tools_on)();
	typedef	DWORD(__stdcall* _type_LPU237_tools_off)();
	typedef	DWORD(__stdcall* _type_LPU237_tools_get_list_w)(wchar_t*);
	typedef	HANDLE(__stdcall* _type_LPU237_tools_open_w)(const wchar_t*);
	typedef	DWORD(__stdcall* _type_LPU237_tools_close)(HANDLE);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_id)(HANDLE, BYTE*);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_start_get_setting)(const BYTE*, type_lpu237_tools_callback_get_parameter, void*);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_start_set_setting)(const BYTE*, type_lpu237_tools_callback_set_parameter, void*);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_cancel)();
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_start_get_setting_except_combination)(const BYTE* sId, type_lpu237_tools_callback_get_parameter cb, void* pUser);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_start_set_setting_except_combination)(const BYTE* sId, type_lpu237_tools_callback_set_parameter cb, void* pUser);


	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_active_and_valied_interface)(HANDLE hDev, BYTE* s_inteface);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_interface)(HANDLE hDev, BYTE c_inteface);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_interface_to_device_and_apply)(HANDLE hDev, BYTE* pc_inteface);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_buzzer)(HANDLE hDev, BYTE* pc_on);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_buzzer)(HANDLE hDev, BYTE c_on);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_language)(HANDLE hDev, BYTE* pc_lang);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_language)(HANDLE hDev, BYTE c_lang);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_track_status)(HANDLE hDev, BYTE* s_status_3_byte);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_track_status)(HANDLE hDev, const BYTE* s_status_3_byte);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_private_tag)(HANDLE hDev, DWORD dw_track_zero_base, BYTE b_prefix, BYTE* s_tag);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_private_tag)(HANDLE hDev, DWORD dw_track_zero_base, BYTE b_prefix, const BYTE* s_tag, DWORD dw_tag);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_ibutton_mode)(HANDLE hDev, BYTE* pc_mode);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_ibutton_mode)(HANDLE hDev, BYTE c_mode);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_ibutton_tag)(HANDLE hDev, BYTE b_remove, BYTE b_prefix, BYTE* s_tag);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_ibutton_tag)(HANDLE hDev, BYTE b_remove, BYTE b_prefix, const BYTE* s_tag, DWORD dw_tag);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_get_ibutton_remove_indication_tag)(HANDLE hDev, BYTE* s_tag);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_ibutton_remove_indication_tag)(HANDLE hDev, const BYTE* s_tag, DWORD dw_tag);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_set_default)(HANDLE hDev);

	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_is_support_msr)(HANDLE hDev, BYTE* pc_support);
	typedef	DWORD(__stdcall* _type_LPU237_tools_msr_is_support_ibutton)(HANDLE hDev, BYTE* pc_support);

public:
	static cdll_lpu237_tools& get_instance()
	{
		static cdll_lpu237_tools obj;
		return obj;
	}

	~cdll_lpu237_tools()
	{
		unload();
	}

	void unload()
	{
		if (m_h_module) {
			FreeLibrary(m_h_module);
			_ini();
		}
	}
	bool load(const std::wstring s_dll_path)
	{
		bool b_result(false);

		do {
			if (m_h_module) {
				b_result = true;
				continue;
			}
			if (s_dll_path.empty())
				continue;

			m_h_module = ::LoadLibrary(s_dll_path.c_str());
			if (!m_h_module) {
				continue;
			}

			m_on = reinterpret_cast<_type_LPU237_tools_on>(::GetProcAddress(m_h_module, "LPU237_tools_on"));
			m_off = reinterpret_cast<_type_LPU237_tools_off>(::GetProcAddress(m_h_module, "LPU237_tools_off"));
			m_get_list = reinterpret_cast<_type_LPU237_tools_get_list_w>(::GetProcAddress(m_h_module, "LPU237_tools_get_list_w"));
			m_open = reinterpret_cast<_type_LPU237_tools_open_w>(::GetProcAddress(m_h_module, "LPU237_tools_open_w"));
			m_close = reinterpret_cast<_type_LPU237_tools_close>(::GetProcAddress(m_h_module, "LPU237_tools_close"));
			m_get_id = reinterpret_cast<_type_LPU237_tools_msr_get_id>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_id"));
			m_start_get_setting = reinterpret_cast<_type_LPU237_tools_msr_start_get_setting>(::GetProcAddress(m_h_module, "LPU237_tools_msr_start_get_setting"));
			m_start_set_setting = reinterpret_cast<_type_LPU237_tools_msr_start_set_setting>(::GetProcAddress(m_h_module, "LPU237_tools_msr_start_set_setting"));
			m_cancel = reinterpret_cast<_type_LPU237_tools_msr_cancel>(::GetProcAddress(m_h_module, "LPU237_tools_msr_cancel"));
			m_start_get_setting_except_combination = reinterpret_cast<_type_LPU237_tools_msr_start_get_setting_except_combination>(::GetProcAddress(m_h_module, "LPU237_tools_msr_start_get_setting_except_combination"));
			m_start_set_setting_except_combination = reinterpret_cast<_type_LPU237_tools_msr_start_set_setting_except_combination>(::GetProcAddress(m_h_module, "LPU237_tools_msr_start_set_setting_except_combination"));

			m_get_interface = reinterpret_cast<_type_LPU237_tools_msr_get_active_and_valied_interface>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_active_and_valied_interface"));
			m_set_interface = reinterpret_cast<_type_LPU237_tools_msr_set_interface>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_interface"));
			m_set_interface_to_device_and_apply = reinterpret_cast<_type_LPU237_tools_msr_set_interface_to_device_and_apply>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_interface_to_device_and_apply"));

			m_get_buzzer = reinterpret_cast<_type_LPU237_tools_msr_get_buzzer>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_buzzer"));
			m_set_buzzer = reinterpret_cast<_type_LPU237_tools_msr_set_buzzer>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_buzzer"));

			m_get_language = reinterpret_cast<_type_LPU237_tools_msr_get_language>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_language"));
			m_set_language = reinterpret_cast<_type_LPU237_tools_msr_set_language>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_language"));

			m_get_track_status = reinterpret_cast<_type_LPU237_tools_msr_get_track_status>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_track_status"));
			m_set_track_status = reinterpret_cast<_type_LPU237_tools_msr_set_track_status>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_track_status"));
			m_get_private_tag = reinterpret_cast<_type_LPU237_tools_msr_get_private_tag>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_private_tag"));
			m_set_private_tag = reinterpret_cast<_type_LPU237_tools_msr_set_private_tag>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_private_tag"));

			m_get_ibutton_mode = reinterpret_cast<_type_LPU237_tools_msr_get_ibutton_mode>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_ibutton_mode"));
			m_set_ibutton_mode = reinterpret_cast<_type_LPU237_tools_msr_set_ibutton_mode>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_ibutton_mode"));

			m_get_ibuton_tag = reinterpret_cast<_type_LPU237_tools_msr_get_ibutton_tag>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_ibutton_tag"));
			m_set_ibuton_tag = reinterpret_cast<_type_LPU237_tools_msr_set_ibutton_tag>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_ibutton_tag"));

			m_get_ibuton_remove = reinterpret_cast<_type_LPU237_tools_msr_get_ibutton_remove_indication_tag>(::GetProcAddress(m_h_module, "LPU237_tools_msr_get_ibutton_remove_indication_tag"));
			m_set_ibutton_remove = reinterpret_cast<_type_LPU237_tools_msr_set_ibutton_remove_indication_tag>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_ibutton_remove_indication_tag"));

			m_set_default = reinterpret_cast<_type_LPU237_tools_msr_set_default>(::GetProcAddress(m_h_module, "LPU237_tools_msr_set_default"));

			m_is_support_msr = reinterpret_cast<_type_LPU237_tools_msr_is_support_msr>(::GetProcAddress(m_h_module, "LPU237_tools_msr_is_support_msr"));
			m_is_support_ibutton = reinterpret_cast<_type_LPU237_tools_msr_is_support_ibutton>(::GetProcAddress(m_h_module, "LPU237_tools_msr_is_support_ibutton"));

			if (!m_on)
				continue;
			if (!m_off)
				continue;
			if (!m_get_list)
				continue;
			if (!m_open)
				continue;
			if (!m_close)
				continue;
			if (!m_get_id)
				continue;
			if (!m_start_get_setting)
				continue;
			if (!m_start_set_setting)
				continue;
			if (!m_cancel)
				continue;
			if (!m_start_get_setting_except_combination)
				continue;
			if (!m_start_set_setting_except_combination)
				continue;

			if (!m_get_interface)
				continue;
			if (!m_set_interface)
				continue;
			if (!m_set_interface_to_device_and_apply)
				continue;
			if (!m_get_buzzer)
				continue;
			if (!m_set_buzzer)
				continue;
			if (!m_get_language)
				continue;
			if (!m_set_language)
				continue;
			if (!m_get_track_status)
				continue;
			if (!m_set_track_status)
				continue;
			if (!m_get_private_tag)
				continue;
			if (!m_set_private_tag)
				continue;
			if (!m_get_ibutton_mode)
				continue;
			if (!m_set_ibutton_mode)
				continue;
			if (!m_get_ibuton_tag)
				continue;
			if (!m_set_ibuton_tag)
				continue;
			if (!m_get_ibuton_remove)
				continue;
			if (!m_set_ibutton_remove)
				continue;
			if (!m_set_default)
				continue;
			if (!m_is_support_msr)
				continue;
			if (!m_is_support_ibutton)
				continue;
			//
			b_result = true;
		} while (false);

		if (!b_result) {
			if (m_h_module) {
				FreeLibrary(m_h_module);
				_ini();
			}
		}
		return b_result;
	}
public://exported methods

	bool on()
	{
		bool b_result(false);
		do {
			if (!m_on)
				continue;
			if (m_on() != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	bool off()
	{
		bool b_result(false);
		do {
			if (!m_off)
				continue;
			if (m_off() != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	size_t get_list(cdll_lpu237_tools::type_list_wstring& list_device)
	{
		do {
			list_device.clear();

			if (!m_get_list)
				continue;

			size_t n_size = m_get_list(NULL);
			if (n_size == 0)
				continue;

			std::vector<wchar_t> v_ws(n_size, 0);
			n_size = m_get_list(&v_ws[0]);
			if (n_size == 0)
				continue;

			if (cdll_lpu237_tools::_get_string_from_multi_string(list_device, &v_ws[0]) == 0)
				continue;
			//
		} while (false);
		return list_device.size();
	}
	HANDLE open(const std::wstring& s_dev_path)
	{
		HANDLE h_result(INVALID_HANDLE_VALUE);
		do {
			if (!m_open)
				continue;

			h_result = m_open(s_dev_path.c_str());
			//
		} while (false);
		return h_result;
	}
	bool close(HANDLE hDev)
	{
		bool b_result(false);
		do {
			if (!m_close)
				continue;
			if (m_close(hDev) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	bool get_id(HANDLE hDev, cdll_lpu237_tools::type_v_id& v_id)
	{
		bool b_result(false);
		do {
			v_id.resize(16, 0);

			if (!m_get_id)
				continue;

			if (m_get_id(hDev, &v_id[0]) == LPU237_TOOLS_RESULT_ERROR)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	bool start_get_setting(const cdll_lpu237_tools::type_v_id& v_id, type_lpu237_tools_callback_get_parameter cb, void* p_user)
	{
		bool b_result(false);
		do {
			if (!m_start_get_setting)
				continue;
			if (m_start_get_setting(&v_id[0], cb, p_user) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	bool start_set_setting(const cdll_lpu237_tools::type_v_id& v_id, type_lpu237_tools_callback_set_parameter cb, void* p_user)
	{
		bool b_result(false);
		do {
			if (!m_start_set_setting)
				continue;
			if (m_start_set_setting(&v_id[0], cb, p_user) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	bool cancel()
	{
		bool b_result(false);
		do {
			if (!m_cancel)
				continue;
			if (m_cancel() != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool start_get_setting_except_combination(const cdll_lpu237_tools::type_v_id& v_id, type_lpu237_tools_callback_get_parameter cb, void* p_user)
	{
		bool b_result(false);
		do {
			if (!m_start_get_setting_except_combination)
				continue;
			if (m_start_get_setting_except_combination(&v_id[0], cb, p_user) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	bool start_set_setting_except_combination(const cdll_lpu237_tools::type_v_id& v_id, type_lpu237_tools_callback_set_parameter cb, void* p_user)
	{
		bool b_result(false);
		do {
			if (!m_start_set_setting_except_combination)
				continue;
			if (m_start_set_setting_except_combination(&v_id[0], cb, p_user) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	/**
	* return acvtive string interface
	*/
	std::wstring get_active_and_valied_interface_by_string(HANDLE h_dev, cdll_lpu237_tools::type_list_wstring& list_valied_interface)
	{
		std::wstring s_inf;

		do {
			list_valied_interface.clear();
			if (!m_get_interface)
				continue;

			DWORD dw_result(LPU237_TOOLS_RESULT_ERROR);
			dw_result = m_get_interface(h_dev, NULL);
			if (dw_result == LPU237_TOOLS_RESULT_ERROR)
				continue;
			if (dw_result == 0)
				continue;
			std::vector<unsigned char> v_inf(dw_result, 0);
			dw_result = m_get_interface(h_dev, &v_inf[0]);
			if (dw_result == LPU237_TOOLS_RESULT_ERROR)
				continue;

			bool b_result(true);
			for (size_t i = 0; i < v_inf.size(); i++) {
				switch (v_inf[i]) {
				case LPU237_TOOLS_INF_USBKB:
					if (i == 0) {
						s_inf = L"USB_KB";
					}
					else {
						list_valied_interface.push_back(L"USB_KB");
					}
					break;
				case LPU237_TOOLS_INF_USBHID:
					if (i == 0) {
						s_inf = L"USB_HID";
					}
					else {
						list_valied_interface.push_back(L"USB_HID");
					}
					break;
				case LPU237_TOOLS_INF_USBVCOM:
					if (i == 0) {
						s_inf = L"USB_VCOM";
					}
					else {
						list_valied_interface.push_back(L"USB_VCOM");
					}
					break;
				case LPU237_TOOLS_INF_UART:
					if (i == 0) {
						s_inf = L"RS232";
					}
					else {
						list_valied_interface.push_back(L"RS232");
					}
					break;
				default:
					b_result = false;
					break;
				}//end switch

				if (!b_result)
					break;//exit for
			}//end for

			if (!b_result) {
				s_inf.clear();
				list_valied_interface.clear();
				continue;
			}
		} while (false);
		return s_inf;
	}

	/**
	* @param s_inf  : "USB_KB", "USB_HID" or L"RS232"
	*/
	bool set_interface_by_string(HANDLE h_dev, const std::wstring& s_inf)
	{
		bool b_result(false);
		unsigned char c_inf(LPU237_TOOLS_INF_USBKB);

		do {
			if (!m_set_interface) {
				continue;
			}
			if (s_inf.compare(L"USB_KB") == 0) {
				c_inf = LPU237_TOOLS_INF_USBKB;
			}
			else if (s_inf.compare(L"USB_HID") == 0) {
				c_inf = LPU237_TOOLS_INF_USBHID;
			}
			else if (s_inf.compare(L"USB_VCOM") == 0) {
				c_inf = LPU237_TOOLS_INF_USBVCOM;
			}
			else if (s_inf.compare(L"RS232") == 0) {
				c_inf = LPU237_TOOLS_INF_UART;
			}
			else {
				continue;
			}

			if (m_set_interface(h_dev, c_inf) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	/**
	* @param s_inf  : "USB_KB", "USB_HID" or L"RS232"
	* @return : first - result, second - interface string before being changed. "USB_KB", "USB_HID" or L"RS232"
	*/
	cdll_lpu237_tools::type_pair_result_string set_interface_to_device_and_apply_by_string(HANDLE h_dev, const std::wstring& s_inf)
	{
		bool b_result(false);
		unsigned char c_inf(LPU237_TOOLS_INF_USBKB);
		std::wstring s_old_inf;

		do {
			if (!m_set_interface_to_device_and_apply) {
				continue;
			}
			if (s_inf.compare(L"USB_KB") == 0) {
				c_inf = LPU237_TOOLS_INF_USBKB;
			}
			else if (s_inf.compare(L"USB_HID") == 0) {
				c_inf = LPU237_TOOLS_INF_USBHID;
			}
			else if (s_inf.compare(L"USB_VCOM") == 0) {
				c_inf = LPU237_TOOLS_INF_USBVCOM;
			}
			else if (s_inf.compare(L"RS232") == 0) {
				c_inf = LPU237_TOOLS_INF_UART;
			}
			else {
				continue;
			}

			if (m_set_interface_to_device_and_apply(h_dev, &c_inf) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			switch (c_inf)
			{
			case LPU237_TOOLS_INF_USBKB:
				s_old_inf = L"USB_KB";
				break;
			case LPU237_TOOLS_INF_USBHID:
				s_old_inf = L"USB_HID";
				break;
			case LPU237_TOOLS_INF_USBVCOM:
				s_old_inf = L"USB_VCOM";
				break;
			case LPU237_TOOLS_INF_UART:
				s_old_inf = L"RS232";
				break;
			default:
				break;
			}//end switch
			//
			b_result = true;
		} while (false);
		return std::make_pair(b_result, s_old_inf);
	}

	/**
	* return : first-result, second - enable(true) or not
	*/
	cdll_lpu237_tools::type_pair_result_enable get_buzzer_status(HANDLE h_dev)
	{
		bool b_result(false), b_enble(false);

		do {
			if (!m_get_buzzer)
				continue;
			unsigned char c_on(0);
			if (m_get_buzzer(h_dev, &c_on) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			if (c_on) {
				b_enble = true;
			}

			b_result = true;
		} while (false);
		return std::make_pair(b_result, b_enble);
	}

	bool set_buzzer_status(HANDLE h_dev, bool b_enable)
	{
		bool b_result(false);

		do {
			if (!m_set_buzzer)
				continue;
			unsigned char c_on(0);
			if (b_enable)
				c_on = 1;
			//
			if (m_set_buzzer(h_dev, c_on) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;

			b_result = true;
		} while (false);
		return b_result;
	}

	cdll_lpu237_tools::type_pair_result_string get_language_by_string(HANDLE h_dev)
	{
		bool b_result(false);
		std::wstring s_lang(L"usa_language");

		do {
			if (!m_get_language)
				continue;
			unsigned char c_lang(LPU237_TOOLS_LANG_USA_ENGLISH);
			if (m_get_language(h_dev, &c_lang) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			switch (c_lang)
			{
			case LPU237_TOOLS_LANG_USA_ENGLISH:
				s_lang = L"usa_english";	break;
			case LPU237_TOOLS_LANG_SPANISH:
				s_lang = L"spanish";	break;
			case LPU237_TOOLS_LANG_DANISH:
				s_lang = L"danish";	break;
			case LPU237_TOOLS_LANG_FRENCH:
				s_lang = L"french";	break;
			case LPU237_TOOLS_LANG_GERMAN:
				s_lang = L"german";	break;
			case LPU237_TOOLS_LANG_ITALIAN:
				s_lang = L"italian";	break;
			case LPU237_TOOLS_LANG_NORWEGIAN:
				s_lang = L"norwegian";	break;
			case LPU237_TOOLS_LANG_SWEDISH:
				s_lang = L"swedish";	break;
			case LPU237_TOOLS_LANG_UK_ENGLISH:
				s_lang = L"uk_english";	break;
			case LPU237_TOOLS_LANG_ISRAEL:
				s_lang = L"hebrew";	break;
			case LPU237_TOOLS_LANG_TURKIYE:
				s_lang = L"turkiye";	break;
			default:
				continue;
			}//end switch
			//
			b_result = true;
		} while (false);
		return std::make_pair(b_result, s_lang);
	}

	bool set_language_by_string(HANDLE h_dev, const std::wstring& s_lang)
	{
		bool b_result(false);

		do {
			if (!m_set_language)
				continue;
			unsigned char c_lang(LPU237_TOOLS_LANG_USA_ENGLISH);

			if (s_lang.compare(L"usa_english") == 0) {
				c_lang = LPU237_TOOLS_LANG_USA_ENGLISH;
			}
			else if (s_lang.compare(L"spanish") == 0) {
				c_lang = LPU237_TOOLS_LANG_SPANISH;
			}
			else if (s_lang.compare(L"danish") == 0) {
				c_lang = LPU237_TOOLS_LANG_DANISH;
			}
			else if (s_lang.compare(L"french") == 0) {
				c_lang = LPU237_TOOLS_LANG_FRENCH;
			}
			else if (s_lang.compare(L"german") == 0) {
				c_lang = LPU237_TOOLS_LANG_GERMAN;
			}
			else if (s_lang.compare(L"italian") == 0) {
				c_lang = LPU237_TOOLS_LANG_ITALIAN;
			}
			else if (s_lang.compare(L"norwegian") == 0) {
				c_lang = LPU237_TOOLS_LANG_NORWEGIAN;
			}
			else if (s_lang.compare(L"swedish") == 0) {
				c_lang = LPU237_TOOLS_LANG_SWEDISH;
			}
			else if (s_lang.compare(L"uk_english") == 0) {
				c_lang = LPU237_TOOLS_LANG_UK_ENGLISH;
			}
			else if (s_lang.compare(L"hebrew") == 0) {
				c_lang = LPU237_TOOLS_LANG_ISRAEL;
			}
			else if (s_lang.compare(L"turkiye") == 0) {
				c_lang = LPU237_TOOLS_LANG_TURKIYE;
			}
			else {
				continue;
			}

			if (m_set_language(h_dev, c_lang) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	/**
	* return : first-result, second - enable(true) or not
	*/
	cdll_lpu237_tools::type_pair_result_enable get_track_status(HANDLE h_dev, int n_zero_base_track)
	{
		bool b_result(false), b_enble(false);

		do {
			if (!m_get_track_status)
				continue;
			if (n_zero_base_track < 0)
				continue;
			if (n_zero_base_track > 2)
				continue;
			//
			unsigned char s_status[] = { 0,0,0 };
			if (m_get_track_status(h_dev, s_status) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;

			if (s_status[n_zero_base_track]) {
				b_enble = true;
			}

			b_result = true;
		} while (false);
		return std::make_pair(b_result, b_enble);
	}

	bool set_track_status(HANDLE h_dev, int n_zero_base_track, bool b_enable)
	{
		bool b_result(false);

		do {
			if (!m_set_track_status)
				continue;
			if (!m_get_track_status)
				continue;
			if (n_zero_base_track < 0)
				continue;
			if (n_zero_base_track > 2)
				continue;
			//
			unsigned char s_status[] = { 0,0,0 };
			if (m_get_track_status(h_dev, s_status) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			if (b_enable)
				s_status[n_zero_base_track] = 1;
			else
				s_status[n_zero_base_track] = 0;
			//
			if (m_set_track_status(h_dev, s_status) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;

			b_result = true;
		} while (false);
		return b_result;
	}

	bool get_msr_private_tag(HANDLE h_dev, int n_zero_base_track, bool b_prefix, type_v_tag& v_tag)
	{
		bool b_result(false);

		do {
			v_tag.resize(0);

			if (!m_get_private_tag)
				continue;
			if (n_zero_base_track < 0)
				continue;
			if (n_zero_base_track > 2)
				continue;

			unsigned char c_prefix(0);
			if (b_prefix)
				c_prefix = 1;

			DWORD dw_size(0);

			dw_size = m_get_private_tag(h_dev, n_zero_base_track, c_prefix, NULL);
			if (dw_size == LPU237_TOOLS_RESULT_ERROR)
				continue;
			if (dw_size == 0) {
				b_result = true;
				continue;
			}

			v_tag.resize(dw_size, 0);
			dw_size = m_get_private_tag(h_dev, n_zero_base_track, c_prefix, &v_tag[0]);
			if (dw_size == LPU237_TOOLS_RESULT_ERROR)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool set_msr_private_tag(HANDLE h_dev, int n_zero_base_track, bool b_prefix, const type_v_tag& v_tag)
	{
		bool b_result(false);

		do {
			if (!m_set_private_tag)
				continue;
			if (n_zero_base_track < 0)
				continue;
			if (n_zero_base_track > 2)
				continue;

			unsigned char c_prefix(0);
			if (b_prefix)
				c_prefix = 1;

			if (v_tag.empty()) {
				if (m_set_private_tag(h_dev, n_zero_base_track, c_prefix, NULL, v_tag.size()) != LPU237_TOOLS_RESULT_SUCCESS)
					continue;
			}
			else {
				if (m_set_private_tag(h_dev, n_zero_base_track, c_prefix, &v_tag[0], v_tag.size()) != LPU237_TOOLS_RESULT_SUCCESS)
					continue;
			}
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	cdll_lpu237_tools::type_pair_result_string get_ibutton_mode_by_string(HANDLE h_dev)
	{
		bool b_result(false);
		std::wstring s_mode(L"usa_language");

		do {
			if (!m_get_ibutton_mode)
				continue;
			unsigned char c_mode(LPU237_TOOLS_IBUTTON_MODE_NONE);
			if (m_get_ibutton_mode(h_dev, &c_mode) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			switch (c_mode)
			{
			case LPU237_TOOLS_IBUTTON_MODE_NONE:
				s_mode = L"None";	break;
			case LPU237_TOOLS_IBUTTON_MODE_ZEROS:
				s_mode = L"Zeros";	break;
			case LPU237_TOOLS_IBUTTON_MODE_F12:
				s_mode = L"F12";	break;
			case LPU237_TOOLS_IBUTTON_MODE_ZEROS7:
				s_mode = L"Zeros7";	break;
			case LPU237_TOOLS_IBUTTON_MODE_ADDMIT:
				s_mode = L"Addimat";	break;
			default:
				continue;
			}//end switch
			//
			b_result = true;
		} while (false);
		return std::make_pair(b_result, s_mode);
	}

	bool set_ibutton_mode_by_string(HANDLE h_dev, const std::wstring& s_mode)
	{
		bool b_result(false);

		do {
			if (!m_set_ibutton_mode)
				continue;
			unsigned char c_mode(LPU237_TOOLS_IBUTTON_MODE_NONE);

			if (s_mode.compare(L"None") == 0) {
				c_mode = LPU237_TOOLS_IBUTTON_MODE_NONE;
			}
			else if (s_mode.compare(L"Zeros") == 0) {
				c_mode = LPU237_TOOLS_IBUTTON_MODE_ZEROS;
			}
			else if (s_mode.compare(L"F12") == 0) {
				c_mode = LPU237_TOOLS_IBUTTON_MODE_F12;
			}
			else if (s_mode.compare(L"Zeros7") == 0) {
				c_mode = LPU237_TOOLS_IBUTTON_MODE_ZEROS7;
			}
			else if (s_mode.compare(L"Addimat") == 0) {
				c_mode = LPU237_TOOLS_IBUTTON_MODE_ADDMIT;
			}
			else {
				continue;
			}

			if (m_set_ibutton_mode(h_dev, c_mode) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool get_ibutton_tag(HANDLE h_dev, bool b_remove, bool b_prefix, type_v_tag& v_tag)
	{
		bool b_result(false);

		do {
			v_tag.resize(0);

			if (!m_get_ibuton_tag)
				continue;

			unsigned char c_remove(0);
			if (b_remove)
				c_remove = 1;
			//
			unsigned char c_prefix(0);
			if (b_prefix)
				c_prefix = 1;

			DWORD dw_size(0);

			dw_size = m_get_ibuton_tag(h_dev, c_remove, c_prefix, NULL);
			if (dw_size == LPU237_TOOLS_RESULT_ERROR)
				continue;
			if (dw_size == 0) {
				b_result = true;
				continue;
			}
			v_tag.resize(dw_size, 0);
			dw_size = m_get_ibuton_tag(h_dev, c_remove, c_prefix, &v_tag[0]);
			if (dw_size == LPU237_TOOLS_RESULT_ERROR)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool set_ibutton_tag(HANDLE h_dev, bool b_remove, bool b_prefix, const type_v_tag& v_tag)
	{
		bool b_result(false);

		do {
			if (!m_set_ibuton_tag)
				continue;

			unsigned char c_remove(0);
			if (b_remove)
				c_remove = 1;

			unsigned char c_prefix(0);
			if (b_prefix)
				c_prefix = 1;

			if (v_tag.empty()) {
				if (m_set_ibuton_tag(h_dev, c_remove, c_prefix, NULL, v_tag.size()) != LPU237_TOOLS_RESULT_SUCCESS)
					continue;
			}
			else {
				if (m_set_ibuton_tag(h_dev, c_remove, c_prefix, &v_tag[0], v_tag.size()) != LPU237_TOOLS_RESULT_SUCCESS)
					continue;
			}
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool get_ibutton_remove_indication_tag(HANDLE h_dev, type_v_tag& v_tag)
	{
		bool b_result(false);

		do {
			v_tag.resize(0);

			if (!m_get_ibuton_remove)
				continue;

			DWORD dw_size(0);

			dw_size = m_get_ibuton_remove(h_dev, NULL);
			if (dw_size == LPU237_TOOLS_RESULT_ERROR)
				continue;
			if (dw_size == 0) {
				b_result = true;
				continue;
			}
			v_tag.resize(dw_size, 0);
			dw_size = m_get_ibuton_remove(h_dev, &v_tag[0]);
			if (dw_size == LPU237_TOOLS_RESULT_ERROR)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool set_ibutton_remove_indication_tag(HANDLE h_dev, const type_v_tag& v_tag)
	{
		bool b_result(false);

		do {
			if (!m_set_ibutton_remove)
				continue;

			if (v_tag.empty()) {
				if (m_set_ibutton_remove(h_dev, NULL, v_tag.size()) != LPU237_TOOLS_RESULT_SUCCESS)
					continue;
			}
			else {
				if (m_set_ibutton_remove(h_dev, &v_tag[0], v_tag.size()) != LPU237_TOOLS_RESULT_SUCCESS)
					continue;
			}
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	bool set_default(HANDLE h_dev)
	{
		bool b_result(false);

		do {
			if (!m_set_default)
				continue;
			if (m_set_default(h_dev) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	/**
	* return : first-result, second - support(true) or not
	*/
	cdll_lpu237_tools::type_pair_result_enable is_support_msr(HANDLE h_dev)
	{
		bool b_result(false), b_support(false);

		do {
			if (!m_is_support_msr)
				continue;
			unsigned char c_support(0);
			if (m_is_support_msr(h_dev, &c_support) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			if (c_support) {
				b_support = true;
			}

			b_result = true;
		} while (false);
		return std::make_pair(b_result, b_support);
	}

	/**
	* return : first-result, second - support(true) or not
	*/
	cdll_lpu237_tools::type_pair_result_enable is_support_ibutton(HANDLE h_dev)
	{
		bool b_result(false), b_support(false);

		do {
			if (!m_is_support_ibutton)
				continue;
			unsigned char c_support(0);
			if (m_is_support_ibutton(h_dev, &c_support) != LPU237_TOOLS_RESULT_SUCCESS)
				continue;
			if (c_support) {
				b_support = true;
			}

			b_result = true;
		} while (false);
		return std::make_pair(b_result, b_support);
	}

private:
	cdll_lpu237_tools()
	{
		_ini();
	}

	void _ini()
	{
		m_h_module = NULL;
		m_on = nullptr;
		m_off = nullptr;

		m_get_list = nullptr;
		m_open = nullptr;
		m_close = nullptr;

		m_get_id = nullptr;

		m_start_get_setting = nullptr;
		m_start_set_setting = nullptr;

		m_start_get_setting_except_combination = nullptr;
		m_start_set_setting_except_combination = nullptr;

		m_cancel = nullptr;

		m_get_interface = nullptr;
		m_set_interface = nullptr;
		m_set_interface_to_device_and_apply = nullptr;

		m_get_buzzer = nullptr;
		m_set_buzzer = nullptr;

		m_get_language = nullptr;
		m_set_language = nullptr;

		m_get_track_status = nullptr;
		m_set_track_status = nullptr;
		m_get_private_tag = nullptr;
		m_set_private_tag = nullptr;

		m_get_ibutton_mode = nullptr;
		m_set_ibutton_mode = nullptr;

		m_get_ibuton_tag = nullptr;
		m_set_ibuton_tag = nullptr;

		m_get_ibuton_remove = nullptr;
		m_set_ibutton_remove = nullptr;

		m_set_default = nullptr;

		m_is_support_msr = nullptr;
		m_is_support_ibutton = nullptr;
	}


	static size_t _get_string_from_multi_string(cdll_lpu237_tools::type_list_wstring& list_string, const wchar_t* sz_multi_string)
	{
		const wchar_t* pDest;
		std::wstring s_temp;
		size_t n_count = 0;
		size_t n_offset = 0;


		do {
			list_string.clear();

			if (!sz_multi_string)
				continue;

			while (sz_multi_string[n_offset] != NULL) {

				pDest = &(sz_multi_string[n_offset]);
				s_temp = pDest;
				list_string.push_back(s_temp);

				n_offset += s_temp.length() + 1;//for passing null termination
				n_count++;
			}//while

		} while (false);
		return n_count;
	}

private:
	HMODULE m_h_module;

	_type_LPU237_tools_on m_on;
	_type_LPU237_tools_off m_off;

	_type_LPU237_tools_get_list_w m_get_list;
	_type_LPU237_tools_open_w m_open;
	_type_LPU237_tools_close m_close;
	_type_LPU237_tools_msr_get_id m_get_id;
	_type_LPU237_tools_msr_start_get_setting m_start_get_setting;
	_type_LPU237_tools_msr_start_set_setting m_start_set_setting;
	_type_LPU237_tools_msr_cancel m_cancel;
	_type_LPU237_tools_msr_start_get_setting_except_combination m_start_get_setting_except_combination;
	_type_LPU237_tools_msr_start_set_setting_except_combination m_start_set_setting_except_combination;

	_type_LPU237_tools_msr_get_active_and_valied_interface m_get_interface;
	_type_LPU237_tools_msr_set_interface m_set_interface;
	_type_LPU237_tools_msr_set_interface_to_device_and_apply m_set_interface_to_device_and_apply;

	_type_LPU237_tools_msr_get_buzzer m_get_buzzer;
	_type_LPU237_tools_msr_set_buzzer m_set_buzzer;
	_type_LPU237_tools_msr_get_language m_get_language;
	_type_LPU237_tools_msr_set_language m_set_language;
	_type_LPU237_tools_msr_get_track_status m_get_track_status;
	_type_LPU237_tools_msr_set_track_status m_set_track_status;
	_type_LPU237_tools_msr_get_private_tag m_get_private_tag;
	_type_LPU237_tools_msr_set_private_tag m_set_private_tag;

	_type_LPU237_tools_msr_get_ibutton_mode m_get_ibutton_mode;
	_type_LPU237_tools_msr_set_ibutton_mode m_set_ibutton_mode;

	_type_LPU237_tools_msr_get_ibutton_tag m_get_ibuton_tag;
	_type_LPU237_tools_msr_set_ibutton_tag m_set_ibuton_tag;

	_type_LPU237_tools_msr_get_ibutton_remove_indication_tag m_get_ibuton_remove;
	_type_LPU237_tools_msr_set_ibutton_remove_indication_tag m_set_ibutton_remove;

	_type_LPU237_tools_msr_set_default m_set_default;

	_type_LPU237_tools_msr_is_support_msr m_is_support_msr;
	_type_LPU237_tools_msr_is_support_ibutton m_is_support_ibutton;

private://don't call these methods
	cdll_lpu237_tools(const cdll_lpu237_tools&);
	cdll_lpu237_tools& operator=(const cdll_lpu237_tools&);

};
