#pragma once

#include <string>
#include <vector>

#include <Windows.h>

class cini
{
public:
    ~cini() {}

    static cini& get_instance()
    {
        static cini obj;
        return obj;
    }

    void set_module(HMODULE h_module)
    {
        m_h_module = h_module;
    }

    std::wstring& get_component_dll_path_without_back_slash_tail()
    {
        return m_s_dll_path;
    }

    /**
    * s_def_ini_file_name_only - ex) lpu230_api.ini or lpu230_fw.ini .......
    */
    bool load_ini_file(const std::wstring& s_ini, const std::wstring& s_def_ini_file_name_and_ext)
    {
        bool b_result(false);

        do {
            if (s_def_ini_file_name_and_ext.empty())
                continue;
            // check exist 
            HANDLE h_file(INVALID_HANDLE_VALUE);
            std::wstring s_cur(L".\\");   s_cur += s_def_ini_file_name_and_ext;

            std::wstring s_ini_abs_path(s_ini);
            std::wstring s_cur_abs_path;

            //path priority
            // 1. currnet path.
            // 2. the given s_ini path.
            s_cur_abs_path = _get_abs_path_from_relative_path(std::wstring(s_cur));
            h_file = CreateFile(s_cur_abs_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (h_file == INVALID_HANDLE_VALUE) {
                if (s_ini_abs_path.empty())
                    continue;
                h_file = CreateFile(s_ini_abs_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (h_file == INVALID_HANDLE_VALUE)
                    continue;
            }
            else {
                s_ini_abs_path = s_cur_abs_path;
            }
            CloseHandle(h_file);
            //
            DWORD dw_result;
            TCHAR s_value[_MAX_PATH];
            int nValue = 0;

            //setting enable property.......
            dw_result = GetPrivateProfileString(L"ini", L"components_path", L"0", s_value, _MAX_PATH, s_ini_abs_path.c_str());
            if (dw_result == 0) {
                continue;
            }

            m_s_dll_path = s_value;

            b_result = true;

        } while (false);


        return b_result;
    }
private:
    cini() :
        m_h_module(NULL)
    {
    }

    std::wstring _get_abs_path_from_relative_path(const std::wstring& s_rel_dll_path)
    {
        bool b_result(false);

        std::wstring s_abs_path;
        do {
            if (s_rel_dll_path.empty())
                continue;

            std::wstring s_abs(_MAX_PATH + 1, 0);
            int n_out_abs(_MAX_PATH);

            _get_abs_path_from_rel_path_in_module(s_abs, n_out_abs, m_h_module, s_rel_dll_path);
            s_abs.shrink_to_fit();
            s_abs_path = s_abs;
        } while (0);

        return s_abs_path;
    }

    //Get abs-path from base path and relative path in given Module as base
    void _get_abs_path_from_rel_path_in_module(std::wstring& sOutAbs, int nOutAbs, HMODULE hModule, const std::wstring& sInRel)
    {
        wchar_t sModuleFN[_MAX_PATH];
        wchar_t Drive[_MAX_DRIVE];
        wchar_t Dir[_MAX_DIR];
        wchar_t Fname[_MAX_FNAME];
        wchar_t Ext[_MAX_EXT];
        wchar_t sBaseFolder[_MAX_PATH];

        if (hModule == NULL)
            return;
        //
        DWORD dw_result = GetModuleFileName(hModule, sModuleFN, _MAX_PATH);
        if (dw_result > 0) {
            //generate realtive from folder to abs folder
            _wsplitpath_s(sModuleFN, Drive, _countof(Drive), Dir, _countof(Dir), Fname, _countof(Fname), Ext, _countof(Ext));
            _wmakepath_s(sBaseFolder, _countof(sBaseFolder), Drive, Dir, NULL, NULL);

            _get_absPath_from_rel_path(sOutAbs, nOutAbs, sBaseFolder, sInRel);
        }
        else {
            dw_result = GetLastError();
        }
    }

    void _get_absPath_from_rel_path(std::wstring& sOutAbs, int nOutAbs, const std::wstring& sInBase, const std::wstring& sInRel)
    {
        wchar_t* pCur = _wgetcwd(NULL, 0);	//save current dirct

        _wchdir(sInBase.c_str());	//change current directory

        std::vector<wchar_t> vOut(nOutAbs + 1, 0);
        _wfullpath(&vOut[0], sInRel.c_str(), nOutAbs);

        _wchdir(pCur);			//recover current directory
        free(pCur);

        sOutAbs = static_cast<wchar_t*>(&vOut[0]);
    }

private:
    HMODULE m_h_module;
    std::wstring m_s_dll_path;

private://don't call these methods
    cini(const cini&);
    cini& operator=(const cini&);


};