#pragma once

#include <Windows.h>

#include <list>
#include <string>
#include <vector>
#include <memory>

#include "tg_lpu237_ibutton.h"

class cdll_lpu237_ibutton
{
public:
	typedef std::vector<unsigned char> type_v_id;
	typedef std::vector<unsigned char> type_v_key;
	typedef std::list<std::wstring> type_list_wstring;
	typedef	std::shared_ptr<cdll_lpu237_ibutton>	type_ptr;
	typedef	std::pair<bool, bool> type_pair_result_enable;
	typedef	std::pair<bool, bool> type_pair_result_cancel;
	typedef	std::pair<bool, DWORD> type_pair_result_index;

private:
	typedef	void (WINAPI* _type_key_callback)(void*);

	typedef	DWORD(WINAPI* _type_LPU237Lock_get_list)(wchar_t*);
	typedef	HANDLE(WINAPI* _type_LPU237Lock_open)(const wchar_t*);

	typedef	DWORD(WINAPI* _type_LPU237Lock_close)(HANDLE);
	typedef	DWORD(WINAPI* _type_LPU237Lock_enable)(HANDLE);
	typedef	DWORD(WINAPI* _type_LPU237Lock_disable)(HANDLE);
	typedef	DWORD(WINAPI* _type_LPU237Lock_cancel_wait_key)(HANDLE);
	typedef	DWORD(WINAPI* _type_LPU237Lock_wait_key_with_callback)(HANDLE, cdll_lpu237_ibutton::_type_key_callback, void*);
	typedef	DWORD(WINAPI* _type_LPU237Lock_get_data)(DWORD, BYTE*);
	typedef	DWORD(WINAPI* _type_LPU237Lock_dll_on)();
	typedef	DWORD(WINAPI* _type_LPU237Lock_dll_off)();
	typedef	DWORD(WINAPI* _type_LPU237Lock_get_id)(HANDLE hDev, BYTE* sId);

public:

	static cdll_lpu237_ibutton& get_instance()
	{
		static cdll_lpu237_ibutton obj;
		return obj;
	}

	~cdll_lpu237_ibutton()
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

			m_get_list = reinterpret_cast<_type_LPU237Lock_get_list>(::GetProcAddress(m_h_module, "LPU237Lock_get_list"));
			m_open = reinterpret_cast<_type_LPU237Lock_open>(::GetProcAddress(m_h_module, "LPU237Lock_open"));
			m_close = reinterpret_cast<_type_LPU237Lock_close>(::GetProcAddress(m_h_module, "LPU237Lock_close"));
			m_enable = reinterpret_cast<_type_LPU237Lock_enable>(::GetProcAddress(m_h_module, "LPU237Lock_enable"));
			m_disable = reinterpret_cast<_type_LPU237Lock_disable>(::GetProcAddress(m_h_module, "LPU237Lock_disable"));
			m_cancel = reinterpret_cast<_type_LPU237Lock_cancel_wait_key>(::GetProcAddress(m_h_module, "LPU237Lock_cancel_wait_key"));

			m_start_get_key = reinterpret_cast<_type_LPU237Lock_wait_key_with_callback>(::GetProcAddress(m_h_module, "LPU237Lock_wait_key_with_callback"));
			m_get_data = reinterpret_cast<_type_LPU237Lock_get_data>(::GetProcAddress(m_h_module, "LPU237Lock_get_data"));
			m_on = reinterpret_cast<_type_LPU237Lock_dll_on>(::GetProcAddress(m_h_module, "LPU237Lock_dll_on"));
			m_off = reinterpret_cast<_type_LPU237Lock_dll_off>(::GetProcAddress(m_h_module, "LPU237Lock_dll_off"));
			m_get_id = reinterpret_cast<_type_LPU237Lock_get_id>(::GetProcAddress(m_h_module, "LPU237Lock_get_id"));


			if (!m_get_list)
				continue;
			if (!m_open)
				continue;
			if (!m_close)
				continue;
			if (!m_enable)
				continue;
			if (!m_disable)
				continue;
			if (!m_cancel)
				continue;
			if (!m_start_get_key)
				continue;
			if (!m_get_data)
				continue;
			if (!m_on)
				continue;
			if (!m_off)
				continue;
			if (!m_get_id)
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
			if (m_on() != LPU237LOCK_DLL_RESULT_SUCCESS)
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
			if (m_off() != LPU237LOCK_DLL_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}
	size_t get_list(cdll_lpu237_ibutton::type_list_wstring& list_device)
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

			if (cdll_lpu237_ibutton::_get_string_from_multi_string(list_device, &v_ws[0]) == 0)
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
			if (m_close(hDev) != LPU237LOCK_DLL_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	cdll_lpu237_ibutton::type_pair_result_enable enable(HANDLE h_dev,bool b_enable)
	{
		bool b_result(false);

		do {
			if (!m_enable)
				continue;
			if (!m_disable)
				continue;

			if (b_enable) {
				if (m_enable(h_dev) != LPU237LOCK_DLL_RESULT_SUCCESS) {
					continue;
				}
			}
			else {
				if (m_disable(h_dev) != LPU237LOCK_DLL_RESULT_SUCCESS) {
					continue;
				}
			}
			b_result = true;
		} while (false);
		return std::make_pair(b_result, b_enable);

	}

	bool cancel(HANDLE h_dev )
	{
		bool b_result(false);
		do {
			if (!m_cancel)
				continue;
			if (m_cancel(h_dev) != LPU237LOCK_DLL_RESULT_SUCCESS)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

	cdll_lpu237_ibutton::type_pair_result_index start_get_key(HANDLE h_dev, type_key_callback cb, void* p_user)
	{
		bool b_result(false);
		DWORD dw_index(LPU237LOCK_DLL_RESULT_ERROR);

		do {
			if (!m_start_get_key)
				continue;
			//
			dw_index = m_start_get_key(h_dev, cb, p_user);
			if (dw_index == LPU237LOCK_DLL_RESULT_ERROR)
				continue;
			//
			b_result = true;
		} while (false);

		return std::make_pair(b_result, dw_index);
	}

	type_pair_result_cancel get_data(DWORD dw_index, cdll_lpu237_ibutton::type_v_key& v_key)
	{
		bool b_result(false);
		bool b_cancel(false);
		DWORD dw_result(LPU237LOCK_DLL_RESULT_ERROR);

		do {
			v_key.resize(0);

			if (!m_get_data)
				continue;
			//
			dw_result = m_get_data(dw_index, NULL);
			if (dw_result == LPU237LOCK_DLL_RESULT_ERROR)
				continue;
			if (dw_result == LPU237LOCK_DLL_RESULT_CANCEL) {
				b_cancel = true;
				continue;
			}

			v_key.resize(dw_result, 0);
			dw_result = m_get_data(dw_index, &v_key[0]);
			if (dw_result == LPU237LOCK_DLL_RESULT_ERROR)
				continue;
			if (dw_result == LPU237LOCK_DLL_RESULT_CANCEL) {
				b_cancel = true;
				continue;
			}
			//
			b_result = true;
		} while (false);

		return std::make_pair(b_result,b_cancel);
	}

	bool get_id(HANDLE hDev, cdll_lpu237_ibutton::type_v_id& v_id)
	{
		bool b_result(false);
		do {
			v_id.resize(16, 0);

			if (!m_get_id)
				continue;

			if (m_get_id(hDev, &v_id[0]) == LPU237LOCK_DLL_RESULT_ERROR)
				continue;
			//
			b_result = true;
		} while (false);
		return b_result;
	}

private:
	cdll_lpu237_ibutton(void)
	{
		_ini();
	}

	void _ini()
	{
		m_h_module = NULL;
		//
		m_get_list = NULL;
		m_open = NULL;
		m_close = NULL;
		m_enable = NULL;
		m_disable = NULL;
		m_cancel = NULL;
		m_start_get_key = NULL;
		m_get_data = NULL;
		m_on = NULL;
		m_off = NULL;
		m_get_id = NULL;
	}

	static size_t _get_string_from_multi_string(cdll_lpu237_ibutton::type_list_wstring& list_string, const wchar_t* sz_multi_string)
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

	cdll_lpu237_ibutton::_type_LPU237Lock_get_list m_get_list;
	cdll_lpu237_ibutton::_type_LPU237Lock_open m_open;
	cdll_lpu237_ibutton::_type_LPU237Lock_close m_close;
	cdll_lpu237_ibutton::_type_LPU237Lock_enable m_enable;
	cdll_lpu237_ibutton::_type_LPU237Lock_disable m_disable;
	cdll_lpu237_ibutton::_type_LPU237Lock_cancel_wait_key m_cancel;
	cdll_lpu237_ibutton::_type_LPU237Lock_wait_key_with_callback m_start_get_key;
	cdll_lpu237_ibutton::_type_LPU237Lock_get_data m_get_data;
	cdll_lpu237_ibutton::_type_LPU237Lock_dll_on m_on;
	cdll_lpu237_ibutton::_type_LPU237Lock_dll_off m_off;
	cdll_lpu237_ibutton::_type_LPU237Lock_get_id m_get_id;

private:
	//don't call these methods
	cdll_lpu237_ibutton(const cdll_lpu237_ibutton&);
	cdll_lpu237_ibutton& operator=(const cdll_lpu237_ibutton&);

};
