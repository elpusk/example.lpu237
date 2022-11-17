#pragma once

#include <list>
#include <string>
#include <utility>

#include <windows.h>

namespace _exam
{
	typedef	std::pair<bool, std::wstring>	type_result_path;

	enum : unsigned int
	{
		const_wnd_msg_get_parameter = WM_APP+100,
		const_wnd_msg_set_parameter = WM_APP + 101,
		const_wnd_msg_get_ibutton = WM_APP + 102

	};

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
