// c_tab_msr.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_tab_msr.h"
#include "afxdialogex.h"

#include "cprogress.h"
// c_tab_msr dialog

IMPLEMENT_DYNAMIC(c_tab_msr, CDialogEx)

c_tab_msr::c_tab_msr(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MSR, pParent)
{

}

c_tab_msr::~c_tab_msr()
{
}

void c_tab_msr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(c_tab_msr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MSR_CONFIG, &c_tab_msr::OnBnClickedButtonMsrConfig)
	ON_BN_CLICKED(IDC_BUTTON_MSR_SENTINELS, &c_tab_msr::OnBnClickedButtonMsrSentinels)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &c_tab_msr::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE_DEFAULT, &c_tab_msr::OnBnClickedButtonRestoreDefault)
END_MESSAGE_MAP()


// c_tab_msr message handlers


void c_tab_msr::OnBnClickedButtonMsrConfig()
{
	c_dlg_msr_config dlg;
	dlg.DoModal();
}


void c_tab_msr::OnBnClickedButtonMsrSentinels()
{
	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	do {
		if (!mgmt.is_selected_device()) {
			AfxMessageBox(L" ERROR : not selected device.");
			continue;
		}
		if (!mgmt.is_support_msr()) {
			AfxMessageBox(L" ERROR : the current device dosen't support MSR-reading");
			continue;
		}

		c_dlg_msr_sentinel dlg;
		dlg.DoModal();
	} while (false);
}


void c_tab_msr::OnBnClickedButtonApply()
{
	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
	if (mgmt.is_loaded_parameter()) {
		cprogress dlg;
		dlg.set_save_mode(true).DoModal();
	}
	else {
		cprogress dlg;
		dlg.set_save_mode(false).DoModal();
	}

}


void c_tab_msr::OnBnClickedButtonRestoreDefault()
{
	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());
	if (mgmt.is_loaded_parameter()) {
		mgmt.set_default();
		AfxMessageBox(L"success set to default. please apply for saving parameters.");
	}
	else {
		AfxMessageBox(L"not loaded device parameters.");
	}
}
