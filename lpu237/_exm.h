#pragma once

#include <list>
#include <string>
#include <utility>

#include <windows.h>
#include <ShlObj.h>
#include <Knownfolders.h>

namespace _exam
{
	typedef	std::pair<bool, std::wstring>	type_result_path;
	typedef	std::pair<std::wstring, bool>	type_pair_string_bool;

	enum : unsigned int
	{
		const_wnd_msg_get_parameter = WM_APP+100,
		const_wnd_msg_set_parameter = WM_APP + 101,
		const_wnd_msg_get_ibutton = WM_APP + 102

	};

	static std::wstring get_known_path(REFKNOWNFOLDERID rfid)
	{
		std::wstring s_path;

		do {
			LPWSTR ps_path;
			if (S_OK != SHGetKnownFolderPath(rfid, 0, NULL, &ps_path))
				continue;
			s_path = ps_path;
			CoTaskMemFree(ps_path);
		} while (false);

		return s_path;
	}

	static std::wstring get_path_ProgramFiles()
	{
		return _exam::get_known_path(FOLDERID_ProgramFiles);
	}
	static std::wstring get_path_ProgramFilesX64()//only for 64bits system
	{
		return _exam::get_known_path(FOLDERID_ProgramFilesX64);
	}

	/**
	* return excluding backslash
	* first : true(current program is x86), false(current x64)
	* second on x86 system : Program Files/Easyset/lpu230/bin/components/x86
	* second on x64 system & 32 bits app : Program Files(x86)/Easyset/lpu230/bin/components/x86
	* second on x64 system & 64 bits app : Program Files/Easyset/lpu230/bin/components/x64
	*/
	static _exam::type_pair_string_bool get_lpu230_component_dll_path()
	{
		std::wstring s_dll_path;
		bool b_x86(true);

		do {
			std::wstring s_programfilesx64(_exam::get_path_ProgramFilesX64());

			if (s_programfilesx64.empty()) {
				// this program is x86( system x86 or x64 )
				s_dll_path = _exam::get_path_ProgramFiles();
				s_dll_path += L"\\Easyset\\lpu230\\bin\\components\\x86";
				continue;
			}

			// this program is x64( system x64 )
			s_dll_path = s_programfilesx64;
			s_dll_path += L"\\Easyset\\lpu230\\bin\\components\\x64";
			b_x86 = false;
		} while (false);
		return std::make_pair(s_dll_path, b_x86);
	}

	static void select_combobox_by_string(CComboBox &combo, const std::wstring& s_sel)
	{
		for (int i = 0; i < combo.GetCount(); i++) {
			CString sData;
			combo.GetLBText(i, sData);
			if (s_sel.compare((LPCTSTR)sData) == 0) {
				combo.SetCurSel(i);
			}
		}//end for
	}

	class cevent {
	public:
		cevent() : m_h_event(CreateEvent(NULL,TRUE,FALSE,NULL))
		{}

		void set()
		{
			if (m_h_event)
				SetEvent(m_h_event);
		}
		void reset()
		{
			if (m_h_event)
				ResetEvent(m_h_event);
		}

		bool wait(unsigned long dw_wait)
		{
			bool b_result(false);

			do {
				if (!m_h_event)
					continue;
				//
				DWORD dw_result = WaitForSingleObject(m_h_event,dw_wait);
				if (dw_result != WAIT_OBJECT_0)
					continue;

				b_result = true;
			} while (false);
			return b_result;
		}

		~cevent()
		{
			if (m_h_event)
				CloseHandle(m_h_event);
		}
	private:
		HANDLE m_h_event;
	};

}
