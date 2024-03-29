// c_dlg_test_water_lock.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_test_water_lock.h"
#include "afxdialogex.h"
#include "cprogress.h"

// c_dlg_test_water_lock dialog

IMPLEMENT_DYNAMIC(c_dlg_test_water_lock, CDialogEx)

c_dlg_test_water_lock::c_dlg_test_water_lock(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST_SUB_WATER_LOCK, pParent)
{

}

c_dlg_test_water_lock::~c_dlg_test_water_lock()
{
}

void c_dlg_test_water_lock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_WATER_LOCK_STATE, m_static_state);
	DDX_Control(pDX, IDC_STATIC_SERIAL_NUMBER, m_static_serial_number);
	DDX_Control(pDX, IDC_COMBO_IBUTTON_TYPE, m_combo_ibutton_type);
	DDX_Control(pDX, IDC_EDIT_START_SENTINEL, m_edit_start_sentinel);
	DDX_Control(pDX, IDC_EDIT_END_SENTINEL, m_edit_stop_sentinel);
	DDX_Control(pDX, IDC_EDIT_PORT_TYPE, m_edit_port_type);
	DDX_Control(pDX, IDC_EDIT_INTERFACE_PORT, m_edit_interface_port);
	DDX_Control(pDX, IDC_COMBO_START, m_combo_start);
	DDX_Control(pDX, IDC_COMBO_END, m_combo_end);
}


BEGIN_MESSAGE_MAP(c_dlg_test_water_lock, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_IBUTTON_TYPE, &c_dlg_test_water_lock::OnCbnSelchangeComboIbuttonType)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &c_dlg_test_water_lock::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &c_dlg_test_water_lock::OnBnClickedOk)
	ON_MESSAGE(_exam::const_wnd_msg_get_ibutton, &c_dlg_test_water_lock::on_get_ibutton)
	ON_CBN_SELCHANGE(IDC_COMBO_START, &c_dlg_test_water_lock::OnCbnSelchangeComboStart)
	ON_CBN_SELCHANGE(IDC_COMBO_END, &c_dlg_test_water_lock::OnCbnSelchangeComboEnd)
END_MESSAGE_MAP()


// c_dlg_test_water_lock message handlers

LRESULT c_dlg_test_water_lock::on_get_ibutton(WPARAM wParam, LPARAM lParam)
{
	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	do {
		_exam::cmgmt_lpu237::type_result_restart_value result(mgmt.get_ibutton_key_in_event_handler(wParam, lParam));
		if (!std::get<0>(result)) {
			AfxMessageBox(L"ERROR reading ibutton");
		}
		if (!std::get<1>(result)) {
			AfxMessageBox(L"ERROR restart ibutton reading test. restart program !");
			continue;
		}

		if (std::get<0>(result)) {
			m_static_serial_number.SetWindowText(std::get<2>(result).c_str());
		}

	} while (false);
	//
	return 0;
}


BOOL c_dlg_test_water_lock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	if (!mgmt.is_loaded_parameter()) {

		cprogress dlg;
		dlg.set_save_mode(false).DoModal();

	}
	cdll_lpu237_tools::type_pair_result_string pair_result_string(false, std::wstring());

	pair_result_string = mgmt.set_active_port_type_to_device_but_not_apply_by_string(L"USB_HID");
	if (pair_result_string.first) {
		m_s_old_interface = pair_result_string.second;
		ATLTRACE(L" : changed inf - %s\n", L"USB_HID");
	}

	//m_static_serial_number;

	m_static_state.SetWindowText(mgmt.get_ibutton_status_by_string().c_str());

	m_edit_port_type.SetWindowText(m_s_old_interface.c_str());
	
	cdll_lpu237_tools::type_list_wstring list_type = mgmt.get_valied_ibutton_mode_by_string();
	for (auto item : list_type) {
		m_combo_ibutton_type.AddString(item.c_str());
	}//end for

	
	pair_result_string = mgmt.get_ibutton_mode_by_string();

	_exam::select_combobox_by_string(m_combo_ibutton_type, pair_result_string.second);

	pair_result_string = mgmt.get_ibutton_tag(true);
	m_edit_start_sentinel.SetWindowText(pair_result_string.second.c_str());

	pair_result_string = mgmt.get_ibutton_tag(false);
	m_edit_stop_sentinel.SetWindowText(pair_result_string.second.c_str());
	
	m_edit_interface_port.SetWindowText(mgmt.get_com_port_by_string().c_str());
	
	//
	m_combo_start.ResetContent();
	m_combo_end.ResetContent();
	for (int i = LPU237_TOOLS_IBUTTON_RANGE_OFFSET_MIN; i <= LPU237_TOOLS_IBUTTON_RANGE_OFFSET_MAX; i++) {
		m_combo_start.AddString(std::to_wstring(i).c_str());
		m_combo_end.AddString(std::to_wstring(i).c_str());
	}//end for

	if (mgmt.is_support_ibutton_range()) {
		m_combo_start.SetCurSel(mgmt.get_ibutton_start_zero_base_offset_of_range().second);
		m_combo_end.SetCurSel(mgmt.get_ibutton_end_zero_base_offset_of_range().second);

		GetDlgItem(IDC_COMBO_START)->EnableWindow();
		GetDlgItem(IDC_COMBO_END)->EnableWindow();
	}
	else {
		GetDlgItem(IDC_COMBO_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_END)->EnableWindow(FALSE);
	}


	//start ibutton test
	if (!mgmt.start_get_ibutton_key(m_hWnd, _exam::const_wnd_msg_get_ibutton)) {
		AfxMessageBox(L"ERROR:start i-button read.");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void c_dlg_test_water_lock::OnCbnSelchangeComboIbuttonType()
{
	do {
		int n_sel = m_combo_ibutton_type.GetCurSel();
		if (n_sel < 0)
			continue;
		CString s_data;
		m_combo_ibutton_type.GetLBText(n_sel, s_data);

		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;
		mgmt.set_ibutton_mode_by_string((LPCTSTR)s_data);
	} while (false);

}

bool c_dlg_test_water_lock::is_exit()
{
	bool b_exit(true);
	cdll_lpu237_tools::type_v_tag v_tag[2];

	do {
		CString s_data;
		std::wstring s_in;
		m_edit_start_sentinel.GetWindowText(s_data);
		s_in = (LPCTSTR)s_data;;

		if (!_exam::cmgmt_lpu237::get_tag_from_string(v_tag[0], s_in, 14)) {
			b_exit = false;
			continue;
		}
		//
		m_edit_stop_sentinel.GetWindowText(s_data);
		s_in = (LPCTSTR)s_data;;

		if (!_exam::cmgmt_lpu237::get_tag_from_string(v_tag[1], s_in, 14)) {
			b_exit = false;
			continue;
		}
		//
	} while (false);

	if (b_exit) {
		//format no error
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (mgmt.is_loaded_parameter()) {
			mgmt.set_ibutton_tag(true, v_tag[0]);
			mgmt.set_ibutton_tag(false, v_tag[1]);
		}
	}
	else {
		if (AfxMessageBox(L"the tag contains a invalied format.\r\n.Do you want to exit?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			b_exit = true;
		}
	}
	return b_exit;
}

void c_dlg_test_water_lock::OnClose()
{
	if (is_exit()) {
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		mgmt.stop_get_ibutton_key_and_exit();
		if (!m_s_old_interface.empty()) {
			//recover interface
			 cdll_lpu237_tools::type_pair_result_string pair_result_string = mgmt.set_active_port_type_to_device_but_not_apply_by_string(m_s_old_interface);
			 if (pair_result_string.first) {
				 ATLTRACE(L" : recoverd inf - %s", m_s_old_interface.c_str());
			 }
		}
		CDialogEx::OnClose();
	}
}


void c_dlg_test_water_lock::OnBnClickedCancel()
{
	//done handler
	if (is_exit()) {
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		mgmt.stop_get_ibutton_key_and_exit();
		if (!m_s_old_interface.empty()) {
			//recover interface
			cdll_lpu237_tools::type_pair_result_string pair_result_string = mgmt.set_active_port_type_to_device_but_not_apply_by_string(m_s_old_interface);
			if (pair_result_string.first) {
				ATLTRACE(L" : recoverd inf - %s", m_s_old_interface.c_str());
			}
		}
		CDialogEx::OnCancel();
	}
}


void c_dlg_test_water_lock::OnBnClickedOk()
{
	//close handler
	if (is_exit()) {
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		mgmt.stop_get_ibutton_key_and_exit();
		if (!m_s_old_interface.empty()) {
			//recover interface
			cdll_lpu237_tools::type_pair_result_string pair_result_string = mgmt.set_active_port_type_to_device_but_not_apply_by_string(m_s_old_interface);
			if (pair_result_string.first) {
				ATLTRACE(L" : recoverd inf - %s", m_s_old_interface.c_str());
			}
		}
		CDialogEx::OnOK();
	}
}


void c_dlg_test_water_lock::OnCbnSelchangeComboStart()
{
	int n_s(m_combo_start.GetCurSel());
	int n_e(m_combo_end.GetCurSel());
	if (n_s > n_e) {
		m_combo_start.SetCurSel(n_e);
	}

	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
	if (mgmt.is_loaded_parameter()) {
		mgmt.set_ibutton_start_zero_base_offset_of_range((unsigned char)m_combo_start.GetCurSel());
	}
}


void c_dlg_test_water_lock::OnCbnSelchangeComboEnd()
{
	int n_s(m_combo_start.GetCurSel());
	int n_e(m_combo_end.GetCurSel());
	if (n_s > n_e) {
		m_combo_end.SetCurSel(n_s);
	}

	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
	if (mgmt.is_loaded_parameter()) {
		mgmt.set_ibutton_end_zero_base_offset_of_range((unsigned char)m_combo_end.GetCurSel());
	}
}
