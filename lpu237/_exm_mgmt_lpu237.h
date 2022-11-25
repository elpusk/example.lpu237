#pragma once

#include <mutex>
#include <thread>
#include <algorithm>
#include <map>
#include <deque>

#include <atltrace.h>

#include "_exm.h"
#include "cdll_lpu237_tools.h"
#include "KBConst.h"
#include "cdll_lpu237_ibutton.h"

namespace _exam
{
	class cmgmt_lpu237
	{
	public:
		typedef	std::tuple<bool, bool, std::wstring>	type_result_restart_value;

	private:
		typedef	std::map<unsigned int, std::wstring> _type_map_hidkey_string;
		typedef	std::map<unsigned char, std::wstring> _type_map_ascii_string;

	public:
		static 	LPARAM make_lparam_with_step(DWORD n_step_index, DWORD n_total_step)
		{
			return(LPARAM)(MAKELONG((WORD)n_step_index, (WORD)n_total_step));
		}
		static DWORD get_step_index_from_lparam(LPARAM lparam)
		{
			return (DWORD)(LOWORD((DWORD)lparam));
		}
		static DWORD get_total_step_from_lparam(LPARAM lparam)
		{
			return (DWORD)(HIWORD((DWORD)lparam));
		}

		static bool is_valied_string_tag_format(const std::wstring& s_tag_in, size_t n_max_size = 14)
		{
			cdll_lpu237_tools::type_v_tag v_tag;
			return _get_tag(v_tag, true, s_tag_in, n_max_size);
		}
		static bool get_tag_from_string(cdll_lpu237_tools::type_v_tag& v_tag, const std::wstring& s_tag_in, size_t n_max_size = 14)
		{
			return _get_tag(v_tag, true, s_tag_in, n_max_size);
		}
		static void get_hex_string_from_bin(std::wstring& s_hex, const cdll_lpu237_tools::type_v_tag& v_bin)
		{
			_get_hex_string_from_bin(s_hex, v_bin);
		}
	private:
		static cdll_lpu237_tools::type_pair_result_string _get_tag_by_string(const cdll_lpu237_tools::type_v_tag& tag, int n_level /*= 1*/, int n_max_key /*= 7*/)
		{
			bool b_hex_mode(true);
			std::wstring stemp;
			bool b_result(true);

			if (n_level < 0) {
				b_hex_mode = false;
				n_level = -n_level;
			}

			do {
				if (tag.empty()) {
					continue;
				}

				if (b_hex_mode) {
					std::wstring s_hex;
					s_hex.clear();
					cmgmt_lpu237::_get_hex_string_from_bin(s_hex, tag);
					stemp += s_hex;
					continue;
				}

				std::wstring s_tag;
				if (cmgmt_lpu237::_get_formated_tag(s_tag, tag, (size_t)n_max_key * 2)) {
					stemp += s_tag;
					continue;
				}

				//stemp += _T(" format error");
				b_result = false;

			} while (false);

			return std::make_pair(b_result, stemp);
		}
		static void _get_hex_string_from_bin(std::wstring& s_hex, const cdll_lpu237_tools::type_v_tag& v_bin)
		{
			CString stemp;

			s_hex = _T("");

			std::for_each(std::begin(v_bin), std::end(v_bin), [&](cdll_lpu237_tools::type_v_tag::value_type c) {
				stemp.Format(_T("%02X"), c);
				s_hex += stemp;
				});

		}

		static 	bool _get_formated_tag(std::wstring& s_out_tag, const cdll_lpu237_tools::type_v_tag& tag, size_t n_max_size = 14)
		{
			bool b_result(false);
			do {
				s_out_tag.clear();

				if (tag.size() > n_max_size)
					continue;
				if (tag.size() % 2 != 0)
					continue;
				//
				if (tag.empty()) {
					s_out_tag = _T("[][]");
				}

				for (size_t i = 0; i < tag.size(); i += 2) {
					if (tag[i] == 0xFF) {
						//tag[i+1] is ASCII code
						std::wstring s_mod_key = cmgmt_lpu237::_get_string_from_ascii(tag[i + 1]);//including []
						s_out_tag += s_mod_key;
						continue;
					}
					else {
						//save status
						s_out_tag += _T('[');
						if (HIDKEY_MOD_L_SFT & tag[i])
							s_out_tag += _T('s');
						if (HIDKEY_MOD_L_CTL & tag[i])
							s_out_tag += _T('c');
						if (HIDKEY_MOD_L_ALT & tag[i])
							s_out_tag += _T('a');
						s_out_tag += _T(']');

						//save key
						s_out_tag += _T('[');
						std::wstring s_key = cmgmt_lpu237::_get_string_from_hidkey((unsigned int)tag[i + 1]);
						if (!s_key.empty())
							s_out_tag += s_key;
						else {
							std::wstring s_hex;
							cdll_lpu237_tools::type_v_tag v_bin;
							v_bin.push_back(tag[i + 1]);
							cmgmt_lpu237::_get_hex_string_from_bin(s_hex, v_bin);
							s_hex = _T("0x") + s_hex;
							s_out_tag += s_hex;
						}
						s_out_tag += _T(']');
					}
				}//end for

				b_result = true;
			} while (0);
			return b_result;
		}

		static const std::wstring& _get_string_from_ascii(unsigned char c_ascii)
		{
			static  cmgmt_lpu237::_type_map_ascii_string map_ascii_string;
			static bool b_first(true);
			static std::wstring s_out;

			if (b_first) {
				b_first = false;
				map_ascii_string['!'] = std::wstring(L"[s][1]");
				map_ascii_string['"'] = std::wstring(L"[s][']");
				map_ascii_string['#'] = std::wstring(L"[s][3]");
				map_ascii_string['$'] = std::wstring(L"[s][4]");
				map_ascii_string['%'] = std::wstring(L"[s][5]");
				map_ascii_string['&'] = std::wstring(L"[s][7]");
				map_ascii_string['\''] = std::wstring(L"[s][']");
				map_ascii_string['('] = std::wstring(L"[s][9]");
				map_ascii_string[')'] = std::wstring(L"[s][0]");
				map_ascii_string['*'] = std::wstring(L"[s][8]");
				map_ascii_string['+'] = std::wstring(L"[s][=]");
				map_ascii_string[','] = std::wstring(L"[][,]");
				map_ascii_string['-'] = std::wstring(L"[][-]");
				map_ascii_string['.'] = std::wstring(L"[][.]");
				map_ascii_string['/'] = std::wstring(L"[][/]");
				map_ascii_string['0'] = std::wstring(L"[][0]");
				map_ascii_string['1'] = std::wstring(L"[][1]");
				map_ascii_string['2'] = std::wstring(L"[][2]");
				map_ascii_string['3'] = std::wstring(L"[][3]");
				map_ascii_string['4'] = std::wstring(L"[][4]");
				map_ascii_string['5'] = std::wstring(L"[][5]");
				map_ascii_string['6'] = std::wstring(L"[][6]");
				map_ascii_string['7'] = std::wstring(L"[][7]");
				map_ascii_string['8'] = std::wstring(L"[][8]");
				map_ascii_string['9'] = std::wstring(L"[][9]");
				map_ascii_string[':'] = std::wstring(L"[s][;]");
				map_ascii_string[';'] = std::wstring(L"[][;]");
				map_ascii_string['<'] = std::wstring(L"[s][,]");
				map_ascii_string['='] = std::wstring(L"[][=]");
				map_ascii_string['>'] = std::wstring(L"[s][.]");
				map_ascii_string['?'] = std::wstring(L"[s][/]");
				map_ascii_string['@'] = std::wstring(L"[s][2]");
				map_ascii_string['A'] = std::wstring(L"[s][a]");
				map_ascii_string['B'] = std::wstring(L"[s][b]");
				map_ascii_string['C'] = std::wstring(L"[s][c]");
				map_ascii_string['D'] = std::wstring(L"[s][d]");
				map_ascii_string['E'] = std::wstring(L"[s][e]");
				map_ascii_string['F'] = std::wstring(L"[s][f]");
				map_ascii_string['G'] = std::wstring(L"[s][g]");
				map_ascii_string['H'] = std::wstring(L"[s][h]");
				map_ascii_string['I'] = std::wstring(L"[s][i]");
				map_ascii_string['J'] = std::wstring(L"[s][j]");
				map_ascii_string['K'] = std::wstring(L"[s][k]");
				map_ascii_string['L'] = std::wstring(L"[s][l]");
				map_ascii_string['M'] = std::wstring(L"[s][m]");
				map_ascii_string['N'] = std::wstring(L"[s][n]");
				map_ascii_string['O'] = std::wstring(L"[s][o]");
				map_ascii_string['P'] = std::wstring(L"[s][p]");
				map_ascii_string['Q'] = std::wstring(L"[s][q]");
				map_ascii_string['R'] = std::wstring(L"[s][r]");
				map_ascii_string['S'] = std::wstring(L"[s][s]");
				map_ascii_string['T'] = std::wstring(L"[s][t]");
				map_ascii_string['U'] = std::wstring(L"[s][u]");
				map_ascii_string['V'] = std::wstring(L"[s][v]");
				map_ascii_string['W'] = std::wstring(L"[s][w]");
				map_ascii_string['X'] = std::wstring(L"[s][x]");
				map_ascii_string['Y'] = std::wstring(L"[s][y]");
				map_ascii_string['Z'] = std::wstring(L"[s][z]");
				map_ascii_string['['] = std::wstring(L"[][[]");
				map_ascii_string['\\'] = std::wstring(L"[][\\]");
				map_ascii_string[']'] = std::wstring(L"[][]]");
				map_ascii_string['^'] = std::wstring(L"[s][6]");
				map_ascii_string['_'] = std::wstring(L"[s][-]");
				map_ascii_string['`'] = std::wstring(L"[][`]");
				map_ascii_string['a'] = std::wstring(L"[][a]");
				map_ascii_string['b'] = std::wstring(L"[][b]");
				map_ascii_string['c'] = std::wstring(L"[][c]");
				map_ascii_string['d'] = std::wstring(L"[][d]");
				map_ascii_string['e'] = std::wstring(L"[][e]");
				map_ascii_string['f'] = std::wstring(L"[][f]");
				map_ascii_string['g'] = std::wstring(L"[][g]");
				map_ascii_string['h'] = std::wstring(L"[][h]");
				map_ascii_string['i'] = std::wstring(L"[][i]");
				map_ascii_string['j'] = std::wstring(L"[][j]");
				map_ascii_string['k'] = std::wstring(L"[][k]");
				map_ascii_string['l'] = std::wstring(L"[][l]");
				map_ascii_string['m'] = std::wstring(L"[][m]");
				map_ascii_string['n'] = std::wstring(L"[][n]");
				map_ascii_string['o'] = std::wstring(L"[][o]");
				map_ascii_string['p'] = std::wstring(L"[][p]");
				map_ascii_string['q'] = std::wstring(L"[][q]");
				map_ascii_string['r'] = std::wstring(L"[][r]");
				map_ascii_string['s'] = std::wstring(L"[][s]");
				map_ascii_string['t'] = std::wstring(L"[][t]");
				map_ascii_string['u'] = std::wstring(L"[][u]");
				map_ascii_string['v'] = std::wstring(L"[][v]");
				map_ascii_string['w'] = std::wstring(L"[][w]");
				map_ascii_string['x'] = std::wstring(L"[][x]");
				map_ascii_string['y'] = std::wstring(L"[][y]");
				map_ascii_string['z'] = std::wstring(L"[][z]");
				map_ascii_string['{'] = std::wstring(L"[s][[]");
				map_ascii_string['|'] = std::wstring(L"[s][\\]");
				map_ascii_string['}'] = std::wstring(L"[s][]]");
				map_ascii_string['~'] = std::wstring(L"[s][`]");
				map_ascii_string[0x0d] = std::wstring(L"[][enter]");
				map_ascii_string[0x20] = std::wstring(L"[][space]");
				map_ascii_string[0x1b] = std::wstring(L"[][esc]");
				map_ascii_string[0x08] = std::wstring(L"[][bs]");
				map_ascii_string[0x09] = std::wstring(L"[][tab]");
			}

			cmgmt_lpu237::_type_map_ascii_string::iterator it = map_ascii_string.find(c_ascii);
			if (it == end(map_ascii_string)) {
				s_out = _T("[][]");
			}
			else {
				s_out = it->second;
			}

			return s_out;
		}

		static const std::wstring& _get_string_from_hidkey(unsigned int n_key)
		{
			static  cmgmt_lpu237::_type_map_hidkey_string map_hidkey_string;
			static bool b_first(true);
			static std::wstring s_empty;

			if (b_first) {
				b_first = false;
				map_hidkey_string[HIDKEY____a____A] = std::wstring(L"a");
				map_hidkey_string[HIDKEY____b____B] = std::wstring(L"b");
				map_hidkey_string[HIDKEY____c____C] = std::wstring(L"c");
				map_hidkey_string[HIDKEY____d____D] = std::wstring(L"d");
				map_hidkey_string[HIDKEY____e____E] = std::wstring(L"e");
				map_hidkey_string[HIDKEY____f____F] = std::wstring(L"f");
				map_hidkey_string[HIDKEY____g____G] = std::wstring(L"g");
				map_hidkey_string[HIDKEY____h____H] = std::wstring(L"h");
				map_hidkey_string[HIDKEY____i____I] = std::wstring(L"i");
				map_hidkey_string[HIDKEY____j____J] = std::wstring(L"j");
				map_hidkey_string[HIDKEY____k____K] = std::wstring(L"k");
				map_hidkey_string[HIDKEY____l____L] = std::wstring(L"l");
				map_hidkey_string[HIDKEY____m____M] = std::wstring(L"m");
				map_hidkey_string[HIDKEY____n____N] = std::wstring(L"n");
				map_hidkey_string[HIDKEY____o____O] = std::wstring(L"o");
				map_hidkey_string[HIDKEY____p____P] = std::wstring(L"p");
				map_hidkey_string[HIDKEY____q____Q] = std::wstring(L"q");
				map_hidkey_string[HIDKEY____r____R] = std::wstring(L"r");
				map_hidkey_string[HIDKEY____s____S] = std::wstring(L"s");
				map_hidkey_string[HIDKEY____t____T] = std::wstring(L"t");
				map_hidkey_string[HIDKEY____u____U] = std::wstring(L"u");
				map_hidkey_string[HIDKEY____v____V] = std::wstring(L"v");
				map_hidkey_string[HIDKEY____w____W] = std::wstring(L"w");
				map_hidkey_string[HIDKEY____x____X] = std::wstring(L"x");
				map_hidkey_string[HIDKEY____y____Y] = std::wstring(L"y");
				map_hidkey_string[HIDKEY____z____Z] = std::wstring(L"z");
				map_hidkey_string[HIDKEY____1_EXCL] = std::wstring(L"1");
				map_hidkey_string[HIDKEY____2_QUOT] = std::wstring(L"2");
				map_hidkey_string[HIDKEY____3_SHAR] = std::wstring(L"3");
				map_hidkey_string[HIDKEY____4_DOLL] = std::wstring(L"4");
				map_hidkey_string[HIDKEY____5_PERC] = std::wstring(L"5");
				map_hidkey_string[HIDKEY____6_CIRC] = std::wstring(L"6");
				map_hidkey_string[HIDKEY____7_AMPE] = std::wstring(L"7");
				map_hidkey_string[HIDKEY____8_ASTE] = std::wstring(L"8");
				map_hidkey_string[HIDKEY____9_L_PA] = std::wstring(L"9");
				map_hidkey_string[HIDKEY____0_R_PA] = std::wstring(L"0");
				map_hidkey_string[HIDKEY____RETURN] = std::wstring(L"enter");
				map_hidkey_string[HIDKEY____ESCAPE] = std::wstring(L"esc");
				map_hidkey_string[HIDKEY_BACKSPACE] = std::wstring(L"bs");
				map_hidkey_string[HIDKEY_______TAB] = std::wstring(L"tab");
				map_hidkey_string[HIDKEY_____SPACE] = std::wstring(L"space");
				map_hidkey_string[HIDKEY_MIN_UNDER] = std::wstring(L"-");
				map_hidkey_string[HIDKEY_EQU__PLUS] = std::wstring(L"=");
				map_hidkey_string[HIDKEY_LBT___LBR] = std::wstring(L"[");
				map_hidkey_string[HIDKEY_RBT___RBR] = std::wstring(L"]");
				map_hidkey_string[HIDKEY_BSLA_VBAR] = std::wstring(L"\\");
				map_hidkey_string[HIDKEY_SEMI__COL] = std::wstring(L";");
				map_hidkey_string[HIDKEY_APOS_QUOT] = std::wstring(L"'");
				map_hidkey_string[HIDKEY_GRAV_TILD] = std::wstring(L"`");
				map_hidkey_string[HIDKEY_COMA___LT] = std::wstring(L",");
				map_hidkey_string[HIDKEY_PERIOD_GT] = std::wstring(L".");
				map_hidkey_string[HIDKEY_SLASH__QM] = std::wstring(L"/");
				map_hidkey_string[HIDKEY________F1] = std::wstring(L"f1");
				map_hidkey_string[HIDKEY________F2] = std::wstring(L"f2");
				map_hidkey_string[HIDKEY________F3] = std::wstring(L"f3");
				map_hidkey_string[HIDKEY________F4] = std::wstring(L"f4");
				map_hidkey_string[HIDKEY________F5] = std::wstring(L"f5");
				map_hidkey_string[HIDKEY________F6] = std::wstring(L"f6");
				map_hidkey_string[HIDKEY________F7] = std::wstring(L"f7");
				map_hidkey_string[HIDKEY________F8] = std::wstring(L"f8");
				map_hidkey_string[HIDKEY________F9] = std::wstring(L"f9");
				map_hidkey_string[HIDKEY_______F10] = std::wstring(L"f10");
				map_hidkey_string[HIDKEY_______F11] = std::wstring(L"f11");
				map_hidkey_string[HIDKEY_______F12] = std::wstring(L"f12");
				map_hidkey_string[HIDKEY____DELETE] = std::wstring(L"del");
			}

			cmgmt_lpu237::_type_map_hidkey_string::iterator it = map_hidkey_string.find(n_key);
			if (it == end(map_hidkey_string))
				return s_empty;
			else
				return it->second;
		}

		static bool _get_tag(cdll_lpu237_tools::type_v_tag& tag, const bool b_enable, const std::wstring& s_tag_in, size_t n_max_size = 14)
		{
			bool b_result(false);
			tag.clear();
			std::wstring s_tag(s_tag_in);

			do {
				if (!b_enable)
					continue;

				std::vector<std::wstring> v_token;

				if (!cmgmt_lpu237::_get_token_from_tag_stream_(v_token, s_tag_in))
					continue;
				if (v_token.size() % 2 != 0)
					continue;
				if (v_token.size() > n_max_size)
					continue;
				//
				bool b_error = false;

				for (size_t i = 0; i < v_token.size(); i++) {
					if (i % 2 == 0) {//key status
						if (std::wstring::npos != v_token[i].find_first_not_of(_T("sca"))) {
							b_error = true;
							break;
						}

						BYTE c_st = 0;
						if (std::wstring::npos != v_token[i].find_first_of(_T("s"))) {
							c_st |= HIDKEY_MOD_L_SFT;
						}
						if (std::wstring::npos != v_token[i].find_first_of(_T("c"))) {
							c_st |= HIDKEY_MOD_L_CTL;
						}
						if (std::wstring::npos != v_token[i].find_first_of(_T("a"))) {
							c_st |= HIDKEY_MOD_L_ALT;
						}
						tag.push_back(c_st);
					}
					else {//key value
						if (v_token[i].empty()) {
							//none tag. therefore remove function key.
							tag.pop_back();
						}
						else if (v_token[i] == std::wstring(_T("f1"))) {
							tag.push_back(HIDKEY________F1);
						}
						else if (v_token[i] == std::wstring(_T("f2"))) {
							tag.push_back(HIDKEY________F2);
						}
						else if (v_token[i] == std::wstring(_T("f3"))) {
							tag.push_back(HIDKEY________F3);
						}
						else if (v_token[i] == std::wstring(_T("f4"))) {
							tag.push_back(HIDKEY________F4);
						}
						else if (v_token[i] == std::wstring(_T("f5"))) {
							tag.push_back(HIDKEY________F5);
						}
						else if (v_token[i] == std::wstring(_T("f6"))) {
							tag.push_back(HIDKEY________F6);
						}
						else if (v_token[i] == std::wstring(_T("f7"))) {
							tag.push_back(HIDKEY________F7);
						}
						else if (v_token[i] == std::wstring(_T("f8"))) {
							tag.push_back(HIDKEY________F8);
						}
						else if (v_token[i] == std::wstring(_T("f9"))) {
							tag.push_back(HIDKEY________F9);
						}
						else if (v_token[i] == std::wstring(_T("f10"))) {
							tag.push_back(HIDKEY_______F10);
						}
						else if (v_token[i] == std::wstring(_T("f11"))) {
							tag.push_back(HIDKEY_______F11);
						}
						else if (v_token[i] == std::wstring(_T("f12"))) {
							tag.push_back(HIDKEY_______F12);
						}
						else if (v_token[i] == std::wstring(_T("esc"))) {
							tag.push_back(HIDKEY____ESCAPE);
						}
						else if (v_token[i] == std::wstring(_T("space"))) {
							tag.push_back(HIDKEY_____SPACE);
						}
						else if (v_token[i] == std::wstring(_T("tab"))) {
							tag.push_back(HIDKEY_______TAB);
						}
						else if (v_token[i] == std::wstring(_T("q"))) {
							tag.push_back(HIDKEY____q____Q);
						}
						else if (v_token[i] == std::wstring(_T("w"))) {
							tag.push_back(HIDKEY____w____W);
						}
						else if (v_token[i] == std::wstring(_T("e"))) {
							tag.push_back(HIDKEY____e____E);
						}
						else if (v_token[i] == std::wstring(_T("r"))) {
							tag.push_back(HIDKEY____r____R);
						}
						else if (v_token[i] == std::wstring(_T("t"))) {
							tag.push_back(HIDKEY____t____T);
						}
						else if (v_token[i] == std::wstring(_T("y"))) {
							tag.push_back(HIDKEY____y____Y);
						}
						else if (v_token[i] == std::wstring(_T("u"))) {
							tag.push_back(HIDKEY____u____U);
						}
						else if (v_token[i] == std::wstring(_T("i"))) {
							tag.push_back(HIDKEY____i____I);
						}
						else if (v_token[i] == std::wstring(_T("o"))) {
							tag.push_back(HIDKEY____o____O);
						}
						else if (v_token[i] == std::wstring(_T("p"))) {
							tag.push_back(HIDKEY____p____P);
						}
						else if (v_token[i] == std::wstring(_T("["))) {
							tag.push_back(HIDKEY_LBT___LBR);
						}
						else if (v_token[i] == std::wstring(_T("]"))) {
							tag.push_back(HIDKEY_RBT___RBR);
						}
						else if (v_token[i] == std::wstring(_T("\\"))) {
							tag.push_back(HIDKEY_BSLA_VBAR);
						}
						else if (v_token[i] == std::wstring(_T("del"))) {
							tag.push_back(HIDKEY____DELETE);
						}
						else if (v_token[i] == std::wstring(_T("z"))) {
							tag.push_back(HIDKEY____z____Z);
						}
						else if (v_token[i] == std::wstring(_T("x"))) {
							tag.push_back(HIDKEY____x____X);
						}
						else if (v_token[i] == std::wstring(_T("c"))) {
							tag.push_back(HIDKEY____c____C);
						}
						else if (v_token[i] == std::wstring(_T("v"))) {
							tag.push_back(HIDKEY____v____V);
						}
						else if (v_token[i] == std::wstring(_T("b"))) {
							tag.push_back(HIDKEY____b____B);
						}
						else if (v_token[i] == std::wstring(_T("n"))) {
							tag.push_back(HIDKEY____n____N);
						}
						else if (v_token[i] == std::wstring(_T("m"))) {
							tag.push_back(HIDKEY____m____M);
						}
						else if (v_token[i] == std::wstring(_T(","))) {
							tag.push_back(HIDKEY_COMA___LT);
						}
						else if (v_token[i] == std::wstring(_T("."))) {
							tag.push_back(HIDKEY_PERIOD_GT);
						}
						else if (v_token[i] == std::wstring(_T("/"))) {
							tag.push_back(HIDKEY_SLASH__QM);
						}
						else if (v_token[i] == std::wstring(_T("`"))) {
							tag.push_back(HIDKEY_GRAV_TILD);
						}
						else if (v_token[i] == std::wstring(_T("1"))) {
							tag.push_back(HIDKEY____1_EXCL);
						}
						else if (v_token[i] == std::wstring(_T("2"))) {
							tag.push_back(HIDKEY____2_QUOT);
						}
						else if (v_token[i] == std::wstring(_T("3"))) {
							tag.push_back(HIDKEY____3_SHAR);
						}
						else if (v_token[i] == std::wstring(_T("4"))) {
							tag.push_back(HIDKEY____4_DOLL);
						}
						else if (v_token[i] == std::wstring(_T("5"))) {
							tag.push_back(HIDKEY____5_PERC);
						}
						else if (v_token[i] == std::wstring(_T("6"))) {
							tag.push_back(HIDKEY____6_CIRC);
						}
						else if (v_token[i] == std::wstring(_T("7"))) {
							tag.push_back(HIDKEY____7_AMPE);
						}
						else if (v_token[i] == std::wstring(_T("8"))) {
							tag.push_back(HIDKEY____8_ASTE);
						}
						else if (v_token[i] == std::wstring(_T("9"))) {
							tag.push_back(HIDKEY____9_L_PA);
						}
						else if (v_token[i] == std::wstring(_T("0"))) {
							tag.push_back(HIDKEY____0_R_PA);
						}
						else if (v_token[i] == std::wstring(_T("-"))) {
							tag.push_back(HIDKEY_MIN_UNDER);
						}
						else if (v_token[i] == std::wstring(_T("="))) {
							tag.push_back(HIDKEY_EQU__PLUS);
						}
						else if (v_token[i] == std::wstring(_T("bs"))) {
							tag.push_back(HIDKEY_BACKSPACE);
						}
						else if (v_token[i] == std::wstring(_T("a"))) {
							tag.push_back(HIDKEY____a____A);
						}
						else if (v_token[i] == std::wstring(_T("s"))) {
							tag.push_back(HIDKEY____s____S);
						}
						else if (v_token[i] == std::wstring(_T("d"))) {
							tag.push_back(HIDKEY____d____D);
						}
						else if (v_token[i] == std::wstring(_T("f"))) {
							tag.push_back(HIDKEY____f____F);
						}
						else if (v_token[i] == std::wstring(_T("g"))) {
							tag.push_back(HIDKEY____g____G);
						}
						else if (v_token[i] == std::wstring(_T("h"))) {
							tag.push_back(HIDKEY____h____H);
						}
						else if (v_token[i] == std::wstring(_T("j"))) {
							tag.push_back(HIDKEY____j____J);
						}
						else if (v_token[i] == std::wstring(_T("k"))) {
							tag.push_back(HIDKEY____k____K);
						}
						else if (v_token[i] == std::wstring(_T("l"))) {
							tag.push_back(HIDKEY____l____L);
						}
						else if (v_token[i] == std::wstring(_T(";"))) {
							tag.push_back(HIDKEY_SEMI__COL);
						}
						else if (v_token[i] == std::wstring(_T("'"))) {
							tag.push_back(HIDKEY_APOS_QUOT);
						}
						else if (v_token[i] == std::wstring(_T("enter"))) {
							tag.push_back(HIDKEY____RETURN);
						}
						else {
							size_t n_pos = v_token[i].find(_T("0x"));
							if (n_pos == std::wstring::npos) {
								b_error = true;
								break;
							}
							std::wstring s_hex = v_token[i].substr(n_pos + 2);//pass 0x
							if (std::wstring::npos != s_hex.find_first_not_of(_T("0123456789abcdef"))) {
								b_error = true;
								break;
							}
							//remove space
							s_hex.erase(unique(begin(s_hex), end(s_hex), [](TCHAR s, TCHAR f) {return (f == _T(' ') || s == _T(' ')); }), s_hex.end());
							if (s_hex.size() > 2) {
								b_error = true;
								break;
							}
							//
							cdll_lpu237_tools::type_v_tag vhex;
							cmgmt_lpu237::_get_bin_from_hex_string(vhex, s_hex);
							tag.push_back((BYTE)vhex[0]);
						}
					}
				}//end for

				if (b_error)
					continue;

				b_result = true;
			} while (0);
			return b_result;
		}

		static bool _get_token_from_tag_stream_(std::vector<std::wstring>& v_token, const std::wstring& s_tag_in)
		{
			bool b_result(true);

			do {
				std::wstring s_tag(s_tag_in);
				std::wstring s_token;

				v_token.clear();

				if (s_tag.empty()) {
					continue;
				}

				std::remove_if(s_tag.begin(), s_tag.end(), isspace);//remove space

				std::deque<std::wstring::value_type> q;
				for (size_t i = 0; i < s_tag.size(); i++) {
					if (s_tag[i] == _T('[')) {
						if (q.empty()) {
							q.push_back(s_tag[i]);
							s_token.clear();//start on token
							continue;
						}
					}
					if (s_tag[i] == _T(']')) {
						if (!q.empty()) {
							if (i == s_tag.size() - 1) {
								q.pop_front();
								v_token.push_back(s_token);
								continue;
							}
							if (s_tag[i + 1] == _T('[')) {
								q.pop_front();
								v_token.push_back(s_token);
								continue;
							}
						}
					}
					//
					if (q.empty()) {
						b_result = false;
						break;
					}
					s_token += s_tag[i];
				}//end for

			} while (false);

			if (!b_result)
				v_token.clear();
			return b_result;
		}

		static void _get_bin_from_hex_string(cdll_lpu237_tools::type_v_tag& vBin, const std::wstring& sHexString)
		{
			vBin.clear();

			if (!cmgmt_lpu237::_is_hex_format_string(sHexString.c_str()))
				return;
			//
			unsigned char cH, cL;
			int nCount(0);

			std::for_each(begin(sHexString), end(sHexString), [&](std::wstring::value_type c) {
				nCount++;
				if (nCount % 2 == 0) {
					//low nibble
					cL = (unsigned char)c;
					if (cL >= '0' && cL <= '9') {
						cL = cL - '0';
					}
					else if (cL >= 'A' && cL <= 'F') {
						cL = cL - 'A' + 10;
					}
					else if (cL >= 'a' && cL <= 'f') {
						cL = cL - 'a' + 10;
					}

					vBin.push_back(cH | cL);
				}
				else {
					//high nibble
					cH = (unsigned char)c;
					if (cH >= '0' && cH <= '9') {
						cH = cH - '0';
					}
					else if (cH >= 'A' && cH <= 'F') {
						cH = cH - 'A' + 10;
					}
					else if (cH >= 'a' && cH <= 'f') {
						cH = cH - 'a' + 10;
					}
					cH <<= 4;
				}
				});
		}
		static bool _is_hex_format_string(LPCTSTR str)
		{
			if (str == NULL)
				return false;
			//
			std::wstring stemp(str);
			if (stemp.size() % 2 != 0)
				return false;
			//
			bool bGood(true);

			std::for_each(std::begin(stemp), std::end(stemp), [&](std::wstring::value_type c) {
				if (bGood) {
					if (c < _T('0'))
						bGood = false;
					if (c > _T('9') && c < _T('A'))
						bGood = false;
					if (c > _T('F') && c < _T('a'))
						bGood = false;
					if (c > _T('f'))
						bGood = false;
				}
				});

			return bGood;
		}

	private:
		typedef	enum : int
		{
			st_undefined = 0,
			st_load_dll,
			st_select_device,
			st_loading_parameter,
			st_loaded_parameter,
			st_saving_parameter,
			st_saved_parameter,
			st_last //this value must be last value. for counting status
		}_type_status;

		typedef	enum : int
		{
			ev_none = 0,
			ev_load_dll,
			ev_unload_dll,
			ev_select_device,
			ev_unselect_device,
			ev_start_loading_parameter,
			ev_end_loading_parameter_with_error,
			ev_end_loading_parameter_with_success,

			ev_start_saving_parameter,
			ev_end_saving_parameter_with_error,
			ev_end_saving_parameter_with_success,
			ev_last //this value must be last value. for counting event
		}_type_event;

		typedef	std::pair< cmgmt_lpu237::_type_status, cmgmt_lpu237::_type_status > _type_pair_old_status_new_status;

	public:
		static cmgmt_lpu237& get_instance()
		{
			static cmgmt_lpu237 obj;
			return obj;
		}

		~cmgmt_lpu237()
		{
			unload_dll();
		}

		bool is_loaded_dll()
		{
			std::lock_guard<std::mutex> lock(m_mutex_status);
			if (m_status == cmgmt_lpu237::st_undefined)
				return false;
			else
				return true;
		}

		bool load_dll()
		{
			bool b_result(false);

			std::lock_guard<std::mutex> lock(m_mutex_status);
			cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
			cdll_lpu237_ibutton& ibutton(cdll_lpu237_ibutton::get_instance());
			do {
				if (m_status != cmgmt_lpu237::st_undefined) {
					b_result = true;
					continue;
				}
				//
				std::wstring s_default_dll_path(_exam::get_lpu230_component_dll_path().first);
				std::wstring s_dll;

				s_dll = s_default_dll_path;
				s_dll += L"\\tg_lpu237_tools.dll";
				if (!tools.load(s_dll)) {
					if (!tools.load(L"tg_lpu237_tools.dll"))//search in current folder.
						continue;
				}
				if (!tools.on())
					continue;
				//
				s_dll = s_default_dll_path;
				s_dll += L"\\tg_lpu237_ibutton.dll";
				if (!ibutton.load(s_dll)) {
					if (!ibutton.load(L"tg_lpu237_ibutton.dll"))//search in current folder.
						continue;
				}
				if (!ibutton.on())
					continue;
				//
				b_result = true;
				_chang_status(ev_load_dll);
			} while (false);

			if (!b_result) {
				tools.off();
				tools.unload();
				//
				ibutton.off();
				ibutton.unload();
			}
			return b_result;
		}

		void unload_dll()
		{
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (m_status == cmgmt_lpu237::st_undefined) {
					continue;
				}

				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				tools.off();
				tools.unload();

				cdll_lpu237_ibutton& ibutton(cdll_lpu237_ibutton::get_instance());
				ibutton.off();
				ibutton.unload();
				//
				_chang_status(ev_unload_dll);
			} while (false);
		}

		_exam::type_result_path select_the_first_device(bool b_force_reselect = false)
		{
			bool b_result(false);
			std::wstring s_path;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (m_status > cmgmt_lpu237::st_select_device) {
					b_result = true;
					s_path = m_s_dev_path;
					continue;
				}
				if (m_status == cmgmt_lpu237::st_undefined) {
					continue;
				}
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				cdll_lpu237_tools::type_list_wstring list_device;
				if (tools.get_list(list_device) == 0)
					continue;

				s_path = *list_device.begin();
				m_h_dev = tools.open(s_path);
				if (m_h_dev == INVALID_HANDLE_VALUE)
					continue;

				m_s_dev_path = s_path;
				b_result = true;

				_chang_status(ev_select_device);
			} while (false);

			return std::make_pair(b_result, s_path);
		}

		bool is_loaded_parameter()
		{
			bool b_result(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;

				b_result = true;
			} while (false);
			return b_result;
		}
		bool start_load_parameter(HWND h_handler, UINT n_msg)
		{
			bool b_result(false);

			std::lock_guard<std::mutex> lock(m_mutex_status);
			cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
			do {
				if (m_status < cmgmt_lpu237::st_select_device) {
					continue;
				}
				if (m_h_dev == INVALID_HANDLE_VALUE)
					continue;

				cdll_lpu237_tools::type_v_id v_id(0);
				if (!tools.get_id(m_h_dev, v_id))
					continue;

				m_h_handler = h_handler;
				m_n_msg = n_msg;

				if (!tools.start_get_setting_except_combination(v_id, cmgmt_lpu237::_cb_get_parameter, this))
					continue;
				//
				b_result = true;
				_chang_status(ev_start_loading_parameter);
			} while (false);

			if (!b_result) {
				if (m_h_dev != INVALID_HANDLE_VALUE) {
					tools.close(m_h_dev);
					m_h_dev = INVALID_HANDLE_VALUE;
				}
			}
			return b_result;
		}
		bool start_save_parameter(HWND h_handler, UINT n_msg)
		{
			bool b_result(false);

			std::lock_guard<std::mutex> lock(m_mutex_status);
			cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
			do {
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				if (m_h_dev == INVALID_HANDLE_VALUE)
					continue;

				cdll_lpu237_tools::type_v_id v_id(0);
				if (!tools.get_id(m_h_dev, v_id))
					continue;

				m_h_handler = h_handler;
				m_n_msg = n_msg;

				if (!tools.start_set_setting_except_combination(v_id, cmgmt_lpu237::_cb_set_parameter, this))
					continue;
				//
				b_result = true;
				_chang_status(ev_start_saving_parameter);
			} while (false);

			if (!b_result) {
				if (m_h_dev != INVALID_HANDLE_VALUE) {
					tools.close(m_h_dev);
					m_h_dev = INVALID_HANDLE_VALUE;
				}
			}
			return b_result;
		}

		cdll_lpu237_tools::type_list_wstring get_valied_port_type_by_string()
		{
			cdll_lpu237_tools::type_list_wstring list_type;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				std::wstring s_active_inf = tools.get_active_and_valied_interface_by_string(m_h_dev, list_type);

			} while (false);
			return list_type;
		}
		std::wstring get_active_port_type_by_string()
		{
			std::wstring s_active_inf;
			cdll_lpu237_tools::type_list_wstring list_type;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				s_active_inf = tools.get_active_and_valied_interface_by_string(m_h_dev, list_type);

			} while (false);
			return s_active_inf;
		}
		bool set_active_port_type_by_string(const std::wstring & s_inf)
		{
			bool b_result(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				b_result = tools.set_interface_by_string(m_h_dev, s_inf);
			} while (false);
			return b_result;
		}
		cdll_lpu237_tools::type_pair_result_string set_active_port_type_to_device_but_not_apply_by_string(const std::wstring& s_inf)
		{
			bool b_result(false);
			std::wstring s_old_inf;
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				std::tie(b_result,s_old_inf) = tools.set_interface_to_device_and_apply_by_string(m_h_dev, s_inf);
			} while (false);
			return std::make_pair(b_result,s_old_inf);
		}

		cdll_lpu237_tools::type_list_wstring get_valied_buzzer_by_string()
		{
			cdll_lpu237_tools::type_list_wstring list_type;

			list_type.push_back(L"Enable");
			list_type.push_back(L"Disable");
			return list_type;
		}

		bool is_enabled_buzzer()
		{
			bool b_result(false);
			bool b_enable(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				std::tie(b_result, b_enable) = tools.get_buzzer_status(m_h_dev);
				if (!b_result)
					continue;

			} while (false);
			return b_enable;
		}

		bool set_buzzer_by_string( const std::wstring & s_status)
		{
			bool b_result(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				if (s_status.compare(L"Enable") == 0) {
					b_result = tools.set_buzzer_status(m_h_dev, true);
				}
				else if (s_status.compare(L"Disable") == 0) {
					b_result = tools.set_buzzer_status(m_h_dev, false);
				}

			} while (false);
			return b_result;
		}

		cdll_lpu237_tools::type_list_wstring get_valied_language_by_string()
		{
			cdll_lpu237_tools::type_list_wstring list_type;

			list_type.push_back(L"usa_english");
			list_type.push_back(L"spanish");
			list_type.push_back(L"danish");
			list_type.push_back(L"french");
			list_type.push_back(L"german");
			list_type.push_back(L"italian");
			list_type.push_back(L"norwegian");
			list_type.push_back(L"swedish");
			list_type.push_back(L"uk_english");
			list_type.push_back(L"hebrew");
			list_type.push_back(L"turkiye");
			return list_type;
		}

		std::wstring get_language_by_string()
		{
			bool b_result(false);
			std::wstring s_lang;
			cdll_lpu237_tools::type_list_wstring list_type;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());
				std::tie(b_result, s_lang) = tools.get_language_by_string(m_h_dev);

			} while (false);
			return s_lang;
		}

		bool set_language_by_string(const std::wstring& s_lang)
		{
			bool b_result(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				b_result = tools.set_language_by_string(m_h_dev,s_lang);

			} while (false);
			return b_result;
		}

		bool is_enable_track(int n_zero_base_track)
		{
			bool b_result(false), b_enable(false);

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				std::tie(b_result, b_enable) = tools.get_track_status(m_h_dev, n_zero_base_track);
			} while (false);
			return b_enable;
		}

		bool set_enable_track(int n_zero_base_track,bool b_enable)
		{
			bool b_result(false);

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				b_result = tools.set_track_status(m_h_dev, n_zero_base_track, b_enable);
			} while (false);
			return b_result;
		}

		cdll_lpu237_tools::type_pair_result_string get_track_private_tag(int n_zero_base_track, bool b_prefix)
		{
			bool b_result(false);
			std::wstring s_tag;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				cdll_lpu237_tools::type_v_tag v_tag;

				if (!tools.get_msr_private_tag(m_h_dev, n_zero_base_track, b_prefix, v_tag))
					continue;

				std::tie(b_result, s_tag) = cmgmt_lpu237::_get_tag_by_string(v_tag, -1, 7);

			} while (false);
			return std::make_pair(b_result, s_tag);
		}

		bool set_track_private_tag(int n_zero_base_track, bool b_prefix, const cdll_lpu237_tools::type_v_tag& v_tag)
		{
			bool b_result(false);
			std::wstring s_tag;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());


				if (!tools.set_msr_private_tag(m_h_dev, n_zero_base_track, b_prefix, v_tag))
					continue;

				b_result = true;
			} while (false);
			return b_result;
		}

		cdll_lpu237_tools::type_list_wstring get_valied_ibutton_mode_by_string()
		{
			cdll_lpu237_tools::type_list_wstring list_type;

			list_type.push_back(L"Zeros");
			list_type.push_back(L"F12");
			list_type.push_back(L"Zeros7");
			list_type.push_back(L"Addimat");
			list_type.push_back(L"None");
			return list_type;
		}

		cdll_lpu237_tools::type_pair_result_string get_ibutton_mode_by_string()
		{
			bool b_result(false);
			std::wstring s_mode;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				std::tie(b_result, s_mode) = tools.get_ibutton_mode_by_string(m_h_dev);
				if (!b_result)
					continue;
			} while (false);
			return std::make_pair(b_result, s_mode);
		}

		bool set_ibutton_mode_by_string(const std::wstring& s_mode)
		{
			bool b_result(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				b_result = tools.set_ibutton_mode_by_string(m_h_dev, s_mode);

			} while (false);
			return b_result;
		}

		cdll_lpu237_tools::type_pair_result_string get_ibutton_tag(bool b_prefix)
		{
			bool b_result(false);
			std::wstring s_tag;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				cdll_lpu237_tools::type_v_tag v_tag;

				if (!tools.get_ibutton_tag(m_h_dev, false, b_prefix, v_tag))
					continue;

				std::tie(b_result, s_tag) = cmgmt_lpu237::_get_tag_by_string(v_tag, -1, 7);

			} while (false);
			return std::make_pair(b_result, s_tag);
		}
		bool set_ibutton_tag(bool b_prefix, const cdll_lpu237_tools::type_v_tag& v_tag)
		{
			bool b_result(false);
			std::wstring s_tag;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());


				if (!tools.set_ibutton_tag(m_h_dev, false, b_prefix, v_tag))
					continue;

				tools.set_ibutton_tag(m_h_dev, true, b_prefix, v_tag);//no condsideratuin error.

				b_result = true;
			} while (false);
			return b_result;
		}

		bool set_default()
		{
			bool b_result(false);
			std::wstring s_tag;

			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_loaded_parameter)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				if (!tools.set_default(m_h_dev))
					continue;

				b_result = true;
			} while (false);
			return b_result;

		}
		cdll_lpu237_tools::type_list_wstring get_valied_com_port_by_string()
		{
			cdll_lpu237_tools::type_list_wstring list_type;

			for (unsigned long i = 1; i <= 20; i++) {
				std::wstring s_temp(L"COM");
				s_temp = s_temp + std::to_wstring(i);
				list_type.push_back(s_temp);
			}//end for
			return list_type;
		}

		std::wstring get_com_port_by_string() const
		{
			return m_s_com_port;
		}

		void set_com_port_by_string(const std::wstring & s_com_port)
		{
			m_s_com_port = s_com_port;
		}


		std::wstring get_ibutton_status_by_string() const
		{
			return std::wstring(L"REMOVED");
		}

		//
		cmgmt_lpu237::type_result_restart_value get_ibutton_key_in_event_handler(WPARAM wparam, LPARAM lparam)
		{
			bool b_result_restart(false);
			bool b_result(false);
			std::wstring s_key;
			
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);

				if (LPU237LOCK_DLL_RESULT_SUCCESS != wparam)
					continue;
				//
				b_result = true;

				if (lparam)
					b_result_restart = true;
				//
				if (!m_v_key.empty()) {
					cmgmt_lpu237::get_hex_string_from_bin(s_key, m_v_key);
					m_v_key.resize(0);
				}

			} while (false);

			return std::make_tuple(b_result,b_result_restart,s_key);
		}

		bool start_get_ibutton_key(HWND h_handler, UINT n_msg)
		{
			bool b_result(false);
			bool b_enable(false);

			std::lock_guard<std::mutex> lock(m_mutex_status);
			cdll_lpu237_ibutton& ibutton(cdll_lpu237_ibutton::get_instance());
			do {
				if (m_status < cmgmt_lpu237::st_select_device) {
					continue;
				}
				m_h_ibutton = ibutton.open(m_s_dev_path);
				if (m_h_ibutton == INVALID_HANDLE_VALUE)
					continue;

				if (!ibutton.enable(m_h_ibutton, true).first)
					continue;

				b_enable = true;
				//
				m_h_handler = h_handler;
				m_n_msg = n_msg;
				m_v_key.resize(0);
				m_evet_for_cancel.reset();

				std::tie(b_result,m_dw_ibutton_result_index) = ibutton.start_get_key(m_h_ibutton, cmgmt_lpu237::_cb_get_ibutton_key, this);
				if(!b_result)
					continue;
				//
				b_result = true;
			} while (false);

			if (!b_result) {
				if (m_h_ibutton != INVALID_HANDLE_VALUE) {

					if (b_enable)
						ibutton.enable(m_h_ibutton,false);
					//
					ibutton.close(m_h_ibutton);
					m_h_ibutton = INVALID_HANDLE_VALUE;
					m_dw_ibutton_result_index = LPU237LOCK_DLL_RESULT_ERROR;
					m_v_key.resize(0);
				}
			}
			return b_result;
		}

		void stop_get_ibutton_key_and_exit()
		{
			std::lock_guard<std::mutex> lock(m_mutex_status);
			cdll_lpu237_ibutton& ibutton(cdll_lpu237_ibutton::get_instance());
			do {
				if (m_status < cmgmt_lpu237::st_select_device) {
					continue;
				}
				if (m_h_ibutton == INVALID_HANDLE_VALUE) {
					continue;
				}
				/*
				if (ibutton.cancel(m_h_ibutton)) {
					//waits inner worker here.
					m_evet_for_cancel.wait(1000);//waits 1 sec.
				}
				ibutton.enable(m_h_ibutton, false);
				*/
				ibutton.close(m_h_ibutton);
				//
				m_h_ibutton = INVALID_HANDLE_VALUE;
				m_h_handler = NULL;
				m_n_msg = 0;
				m_v_key.resize(0);
			} while (false);
		}

		bool is_selected_device()
		{
			bool b_result(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_select_device)
					continue;
				//
				b_result = true;
			} while (false);
			return b_result;
		}
		bool is_support_msr()
		{
			bool b_result(false);
			bool b_support(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_select_device)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				std::tie(b_result, b_support) = tools.is_support_msr(m_h_dev);
				if (!b_result)
					continue;

			} while (false);
			return b_support;
		}

		bool is_support_ibutton()
		{
			bool b_result(false);
			bool b_support(false);
			do {
				std::lock_guard<std::mutex> lock(m_mutex_status);
				if (_chang_status(ev_none).first < st_select_device)
					continue;
				cdll_lpu237_tools& tools(cdll_lpu237_tools::get_instance());

				std::tie(b_result, b_support) = tools.is_support_ibutton(m_h_dev);
				if (!b_result)
					continue;

			} while (false);
			return b_support;
		}

	private:
		cmgmt_lpu237()
		{
			_ini();
		}

		void _ini()
		{
			m_status = cmgmt_lpu237::st_undefined;
			m_h_dev = INVALID_HANDLE_VALUE;

			m_h_ibutton = INVALID_HANDLE_VALUE;
			m_s_dev_path.clear();

			m_dw_ibutton_result_index = LPU237LOCK_DLL_RESULT_ERROR;

			m_h_handler = NULL;
			m_n_msg = 0;

			m_s_com_port = L"COM1";

			m_v_key.resize(0);
		}

		/**
		 * .
		 * 
		 * \param p_user
		 * \param dw_current_step_result : LPU237_TOOLS_RESULT_x
		 * \param dw_zero_base_current_step : zero-base index.
		 * \param dw_total_step : step index >= 0 and step index < this value
		 * \return 
		 */
		static DWORD __stdcall _cb_get_parameter(void* p_user, DWORD dw_current_step_result, DWORD dw_zero_base_current_step, DWORD dw_total_step)
		{
			DWORD dw_result(LPU237_TOOLS_RESULT_SUCCESS);
			cmgmt_lpu237* p_obj = (cmgmt_lpu237*)p_user;

			do {
				if (!p_obj)
					continue;
				//
				std::lock_guard<std::mutex> lock(p_obj->m_mutex_status);

				ATLTRACE(L"(result, cur_step, total ) = (%u, %u, %u)\n", dw_current_step_result, dw_zero_base_current_step+1, dw_total_step);
				if (dw_current_step_result != LPU237_TOOLS_RESULT_SUCCESS) {
					//complete with error
					p_obj->_chang_status(ev_end_loading_parameter_with_error);
					continue;
				}
				if ((dw_zero_base_current_step + 1) == dw_total_step) {
					//complete with success
					p_obj->_chang_status(ev_end_loading_parameter_with_success);
					continue;
				}

			} while (false);

			if (p_obj) {
				::PostMessage(p_obj->m_h_handler, p_obj->m_n_msg, (WPARAM)dw_current_step_result, make_lparam_with_step(dw_zero_base_current_step, dw_total_step));
			}
			return dw_result;
		}

		/**
		 * .
		 * 
		 * \param p_user
		 * \param dw_current_step_result
		 * \param dw_zero_base_current_step
		 * \param dw_total_step
		 * \param dw_reserved
		 * \return 
		 */
		static DWORD __stdcall _cb_set_parameter(void* p_user, DWORD dw_current_step_result, DWORD dw_zero_base_current_step, DWORD dw_total_step, DWORD dw_reserved)
		{
			DWORD dw_result(LPU237_TOOLS_RESULT_SUCCESS);
			cmgmt_lpu237* p_obj = (cmgmt_lpu237*)p_user;

			do {
				if (!p_obj)
					continue;
				//
				std::lock_guard<std::mutex> lock(p_obj->m_mutex_status);

				ATLTRACE(L"(result, cur_step, total ) = (%u, %u, %u)\n", dw_current_step_result, dw_zero_base_current_step + 1, dw_total_step);
				if (dw_current_step_result != LPU237_TOOLS_RESULT_SUCCESS) {
					//complete with error
					p_obj->_chang_status(ev_end_saving_parameter_with_error);
					continue;
				}
				if ((dw_zero_base_current_step + 1) == dw_total_step) {
					//complete with success
					p_obj->_chang_status(ev_end_saving_parameter_with_success);
					continue;
				}


			} while (false);

			if (p_obj) {
				::PostMessage(p_obj->m_h_handler, p_obj->m_n_msg, (WPARAM)dw_current_step_result, make_lparam_with_step(dw_zero_base_current_step, dw_total_step));
			}
			return dw_result;
		}

		/**
		 * callback of ibutton key.
		 * 
		 * \param p_user
		 * \return 
		 */
		static void __stdcall _cb_get_ibutton_key(void* p_user)
		{
			cmgmt_lpu237* p_obj = (cmgmt_lpu237*)p_user;
			DWORD dw_result(LPU237LOCK_DLL_RESULT_ERROR);
			LPARAM restart_result(0);
			do {
				if (!p_obj)
					continue;
				//
				std::lock_guard<std::mutex> lock(p_obj->m_mutex_status);
				cdll_lpu237_ibutton& ibutton(cdll_lpu237_ibutton::get_instance());

				p_obj->m_v_key.resize(0);

				cdll_lpu237_ibutton::type_pair_result_cancel result_cancel = ibutton.get_data(p_obj->m_dw_ibutton_result_index, p_obj->m_v_key);
				if (!result_cancel.first) {
					if (result_cancel.second)
						p_obj->m_evet_for_cancel.set();
					//
					continue;
				}
				
				bool b_result(false);
				p_obj->m_evet_for_cancel.reset();
				//
				std::tie(b_result, p_obj->m_dw_ibutton_result_index) = ibutton.start_get_key(p_obj->m_h_ibutton, cmgmt_lpu237::_cb_get_ibutton_key, p_obj);
				if (b_result)
					restart_result = 1;
				//
				dw_result = LPU237LOCK_DLL_RESULT_SUCCESS;
			} while (false);

			if (p_obj) {
				::PostMessage(p_obj->m_h_handler, p_obj->m_n_msg, (WPARAM)dw_result, restart_result);
			}
		}
		
	private:
		std::mutex m_mutex_status;//don't use in private methods. except static method
		cmgmt_lpu237::_type_status m_status;

		HANDLE m_h_dev;
		std::wstring m_s_dev_path;

		HANDLE m_h_ibutton;
		DWORD m_dw_ibutton_result_index;

		HWND m_h_handler;
		UINT m_n_msg;
		std::wstring m_s_com_port;

		cdll_lpu237_ibutton::type_v_key m_v_key;
		_exam::cevent m_evet_for_cancel;

	private:
		_type_pair_old_status_new_status _chang_status(cmgmt_lpu237::_type_event ev)
		{
			static cmgmt_lpu237::_type_status st_table[cmgmt_lpu237::ev_last][cmgmt_lpu237::st_last] =
			{
/*										*//*st_undefined, st_load_dll,		st_select_device,		st_loading_parameter,	st_loaded_parameter,	st_saving_parameter,	st_saved_parameter*/
/*ev_none								*/{st_undefined,st_load_dll,		st_select_device,		st_loading_parameter,	st_loaded_parameter,	st_saving_parameter,	st_saved_parameter},
/*ev_load_dll							*/{st_load_dll,	st_load_dll,		st_select_device,		st_loading_parameter,	st_loaded_parameter,	st_saving_parameter,	st_saved_parameter},
/*ev_unload_dll							*/{st_undefined,st_undefined,		st_undefined,			st_loading_parameter,	st_undefined,			st_saving_parameter,	st_undefined},
/*ev_select_device						*/{st_undefined,st_select_device,	st_select_device,		st_loading_parameter,	st_select_device,		st_saving_parameter,	st_select_device},
/*ev_unselect_device					*/{st_undefined,st_load_dll,		st_load_dll,			st_loading_parameter,	st_load_dll,			st_saving_parameter,	st_load_dll},
/*ev_start_loading_parameter			*/{st_undefined,st_load_dll,		st_loading_parameter,	st_loading_parameter,	st_loading_parameter,	st_saving_parameter,	st_loading_parameter},
/*ev_end_loading_parameter_with_error	*/{st_undefined,st_load_dll,		st_select_device,		st_select_device,		st_loaded_parameter,	st_saving_parameter,	st_saved_parameter},
/*ev_end_loading_parameter_with_success	*/{st_undefined,st_load_dll,		st_select_device,		st_loaded_parameter,	st_loaded_parameter,	st_saving_parameter,	st_saved_parameter},
/*ev_start_saving_parameter				*/{st_undefined,st_load_dll,		st_select_device,		st_loaded_parameter,	st_saving_parameter,	st_saving_parameter,	st_saving_parameter},
/*ev_end_saving_parameter_with_error	*/{st_undefined,st_load_dll,		st_select_device,		st_loaded_parameter,	st_loaded_parameter,	st_loaded_parameter,	st_saved_parameter},
/*ev_end_saving_parameter_with_success	*/{st_undefined,st_load_dll,		st_select_device,		st_loaded_parameter,	st_loaded_parameter,	st_saved_parameter,		st_saved_parameter}

			};

			cmgmt_lpu237::_type_status st_old(m_status), st_new(m_status);
			m_status = st_new = st_table[ev][m_status];

			return std::make_pair(st_old, st_new);
		}

	private://don't call these methods.
		cmgmt_lpu237(const cmgmt_lpu237&);
		cmgmt_lpu237& operator=(const cmgmt_lpu237&);
	};

}
