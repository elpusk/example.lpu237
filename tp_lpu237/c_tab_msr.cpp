// c_tab_msr.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_tab_msr.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// c_tab_msr message handlers


void c_tab_msr::OnBnClickedButtonMsrConfig()
{
	// TODO: Add your control notification handler code here
}


void c_tab_msr::OnBnClickedButtonMsrSentinels()
{
	c_dlg_msr_sentinel dlg;

	dlg.DoModal();
}
