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
		const_wnd_msg_set_parameter = WM_APP + 101
	};


}
