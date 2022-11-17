// c_dlg_msr_config.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_msr_config.h"
#include "afxdialogex.h"
#include "cprogress.h"

// c_dlg_msr_config dialog

IMPLEMENT_DYNAMIC(c_dlg_msr_config, CDialogEx)

c_dlg_msr_config::c_dlg_msr_config(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MSR_SUB_CONFIG, pParent)
{

}

c_dlg_msr_config::~c_dlg_msr_config()
{
}

void c_dlg_msr_config::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT_TYPE, m_combo_port_type);
	DDX_Control(pDX, IDC_COMBO_INTERFACE_PORT, m_combo_interface_type);
	DDX_Control(pDX, IDC_COMBO_BUZZER, m_combo_buzzer);
	DDX_Control(pDX, IDC_COMBO_KEYBOARD_LANGUAGE, m_combo_keyboard_language);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_config, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT_TYPE, &c_dlg_msr_config::OnCbnSelchangeComboPortType)
	ON_CBN_SELCHANGE(IDC_COMBO_INTERFACE_PORT, &c_dlg_msr_config::OnCbnSelchangeComboInterfacePort)
	ON_CBN_SELCHANGE(IDC_COMBO_BUZZER, &c_dlg_msr_config::OnCbnSelchangeComboBuzzer)
	ON_CBN_SELCHANGE(IDC_COMBO_KEYBOARD_LANGUAGE, &c_dlg_msr_config::OnCbnSelchangeComboKeyboardLanguage)
END_MESSAGE_MAP()


// c_dlg_msr_config message handlers


BOOL c_dlg_msr_config::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	if (!mgmt.is_loaded_parameter()) {

		cprogress dlg;
		dlg.set_save_mode(false).DoModal();

	}

	//
	// ini components
	cdll_lpu237_tools::type_list_wstring list_port_type = mgmt.get_valied_port_type_by_string();

	for (auto item : list_port_type) {
		m_combo_port_type.AddString(item.c_str());
	}//end for


	cdll_lpu237_tools::type_list_wstring list_com_port_number = mgmt.get_valied_com_port_by_string();
	for (auto item : list_com_port_number) {
		m_combo_interface_type.AddString(item.c_str());
	}//end for

	list_port_type = mgmt.get_valied_buzzer_by_string();
	for (auto item : list_port_type) {
		m_combo_buzzer.AddString(item.c_str());
	}//end for


	list_port_type = mgmt.get_valied_language_by_string();
	for (auto item : list_port_type) {
		m_combo_keyboard_language.AddString(item.c_str());
	}//end for

	//
	// ini selection
	_exam::select_combobox_by_string(m_combo_port_type, mgmt.get_active_port_type_by_string());
	m_combo_interface_type.SetCurSel(0);

	if (mgmt.is_enabled_buzzer()) {
		_exam::select_combobox_by_string(m_combo_buzzer, L"Enable");
	}
	else {
		_exam::select_combobox_by_string(m_combo_buzzer, L"Disable");
	}

	_exam::select_combobox_by_string(m_combo_keyboard_language, mgmt.get_language_by_string());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



void c_dlg_msr_config::OnCbnSelchangeComboPortType()
{
	do {
		int n_sel = m_combo_port_type.GetCurSel();
		if (n_sel < 0)
			continue;
		CString s_data;
		m_combo_port_type.GetLBText(n_sel, s_data);

		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;
		mgmt.set_active_port_type_by_string((LPCTSTR)s_data);
	} while (false);
}


void c_dlg_msr_config::OnCbnSelchangeComboInterfacePort()
{
	do {
		int n_sel = m_combo_interface_type.GetCurSel();
		if (n_sel < 0)
			continue;
		CString s_data;
		m_combo_interface_type.GetLBText(n_sel, s_data);

		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;
		mgmt.set_com_port_by_string((LPCTSTR)s_data);
	} while (false);

}


void c_dlg_msr_config::OnCbnSelchangeComboBuzzer()
{
	do {
		int n_sel = m_combo_buzzer.GetCurSel();
		if (n_sel < 0)
			continue;
		CString s_data;
		m_combo_buzzer.GetLBText(n_sel, s_data);

		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;
		mgmt.set_buzzer_by_string((LPCTSTR)s_data);
	} while (false);

}


void c_dlg_msr_config::OnCbnSelchangeComboKeyboardLanguage()
{
	do {
		int n_sel = m_combo_keyboard_language.GetCurSel();
		if (n_sel < 0)
			continue;
		CString s_data;
		m_combo_keyboard_language.GetLBText(n_sel, s_data);

		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;
		mgmt.set_language_by_string((LPCTSTR)s_data);
	} while (false);

}

