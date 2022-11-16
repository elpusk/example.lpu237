// c_dlg_msr_sentinel.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_msr_sentinel.h"
#include "afxdialogex.h"
#include "cprogress.h"

// c_dlg_msr_sentinel dialog

IMPLEMENT_DYNAMIC(c_dlg_msr_sentinel, CDialogEx)

c_dlg_msr_sentinel::c_dlg_msr_sentinel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MSR_SUB_SENTINELS, pParent)
{

}

c_dlg_msr_sentinel::~c_dlg_msr_sentinel()
{
}

void c_dlg_msr_sentinel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ISO1_START_SENTINEL, m_edit_iso_start_sentinel[0]);
	DDX_Control(pDX, IDC_EDIT_ISO2_START_SENTINEL, m_edit_iso_start_sentinel[1]);
	DDX_Control(pDX, IDC_EDIT_ISO3_START_SENTINEL, m_edit_iso_start_sentinel[2]);
	DDX_Control(pDX, IDC_EDIT_ISO1_END_SENTINEL, m_edit_iso_end_sentinel[0]);
	DDX_Control(pDX, IDC_EDIT_ISO2_END_SENTINEL, m_edit_iso_end_sentinel[1]);
	DDX_Control(pDX, IDC_EDIT_ISO3_END_SENTINEL, m_edit_iso_end_sentinel[2]);
	DDX_Control(pDX, IDC_CHECK_ISO1, m_check_enable_iso[0]);
	DDX_Control(pDX, IDC_CHECK_ISO2, m_check_enable_iso[1]);
	DDX_Control(pDX, IDC_CHECK_ISO3, m_check_enable_iso[2]);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_sentinel, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_ISO1, &c_dlg_msr_sentinel::OnBnClickedCheckIso1)
	ON_BN_CLICKED(IDC_CHECK_ISO2, &c_dlg_msr_sentinel::OnBnClickedCheckIso2)
	ON_BN_CLICKED(IDC_CHECK_ISO3, &c_dlg_msr_sentinel::OnBnClickedCheckIso3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// c_dlg_msr_sentinel message handlers


BOOL c_dlg_msr_sentinel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	if (!mgmt.is_loaded_parameter()) {

		cprogress dlg;
		dlg.set_save_mode(false).DoModal();

	}

	cdll_lpu237_tools::type_pair_result_string pair_result_string(false,std::wstring());

	for (int i = 0; i < 3; i++) {
		if (mgmt.is_enable_track(i))
			m_check_enable_iso[i].SetCheck(BST_CHECKED);
		else
			m_check_enable_iso[i].SetCheck(BST_UNCHECKED);
		//
		pair_result_string = mgmt.get_track_private_tag(i, true);
		if (pair_result_string.first)
			m_edit_iso_start_sentinel[i].SetWindowText(pair_result_string.second.c_str());
		//
		pair_result_string = mgmt.get_track_private_tag(i, false);
		if (pair_result_string.first)
			m_edit_iso_end_sentinel[i].SetWindowText(pair_result_string.second.c_str());

	}//end for

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void c_dlg_msr_sentinel::OnBnClickedCheckIso1()
{
	int i(0);

	do {
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;

		if (m_check_enable_iso[i].GetCheck() == BST_CHECKED) {
			mgmt.set_enable_track(i, true);
			continue;
		}

		mgmt.set_enable_track(i, false);

	} while (false);
}


void c_dlg_msr_sentinel::OnBnClickedCheckIso2()
{
	int i(1);

	do {
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;

		if (m_check_enable_iso[i].GetCheck() == BST_CHECKED) {
			mgmt.set_enable_track(i, true);
			continue;
		}

		mgmt.set_enable_track(i, false);

	} while (false);
}


void c_dlg_msr_sentinel::OnBnClickedCheckIso3()
{
	int i(2);

	do {
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (!mgmt.is_loaded_parameter())
			continue;

		if (m_check_enable_iso[i].GetCheck() == BST_CHECKED) {
			mgmt.set_enable_track(i, true);
			continue;
		}

		mgmt.set_enable_track(i, false);

	} while (false);
}


void c_dlg_msr_sentinel::OnClose()
{
	bool b_exit(true);
	cdll_lpu237_tools::type_v_tag v_tag[2][3];

	do {
		CString s_data;
		std::wstring s_in;
		for (int i = 0; i < 3; i++) {
			m_edit_iso_start_sentinel[i].GetWindowText(s_data);
			s_in = (LPCTSTR)s_data;;

			if (!_exam::cmgmt_lpu237::get_tag_from_string(v_tag[0][i],s_in, 14)) {
				b_exit = false;
				break;
			}
			//
			m_edit_iso_end_sentinel[i].GetWindowText(s_data);
			s_in = (LPCTSTR)s_data;;

			if (!_exam::cmgmt_lpu237::get_tag_from_string(v_tag[1][i], s_in, 14)) {
				b_exit = false;
				break;
			}

		}//exit for
		//
	} while (false);

	if (b_exit) {
		//format no error
		_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
		if (mgmt.is_loaded_parameter()) {
			for (int i = 0; i < 3; i++) {
				mgmt.set_track_private_tag(i, true, v_tag[0][i]);
				mgmt.set_track_private_tag(i, false, v_tag[1][i]);
			}//end for
		}
		CDialogEx::OnClose();
	}
	else {
		if (AfxMessageBox(L"the tag contains a invalied format.\r\n.Do you want to exit?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			CDialogEx::OnClose();
		}
	}
}
