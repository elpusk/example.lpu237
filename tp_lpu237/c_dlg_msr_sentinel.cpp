// c_dlg_msr_sentinel.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_msr_sentinel.h"
#include "afxdialogex.h"


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
	DDX_Control(pDX, IDC_EDIT_ISO1_START_SENTINEL, m_edit_iso1_start_sentinel[0]);
	DDX_Control(pDX, IDC_EDIT_ISO2_START_SENTINEL, m_edit_iso1_start_sentinel[1]);
	DDX_Control(pDX, IDC_EDIT_ISO3_START_SENTINEL, m_edit_iso1_start_sentinel[2]);
	DDX_Control(pDX, IDC_EDIT_ISO1_END_SENTINEL, m_edit_iso1_end_sentinel[0]);
	DDX_Control(pDX, IDC_EDIT_ISO2_END_SENTINEL, m_edit_iso1_end_sentinel[1]);
	DDX_Control(pDX, IDC_EDIT_ISO3_END_SENTINEL, m_edit_iso1_end_sentinel[2]);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_sentinel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &c_dlg_msr_sentinel::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE_DEFAULT, &c_dlg_msr_sentinel::OnBnClickedButtonRestoreDefault)
END_MESSAGE_MAP()


// c_dlg_msr_sentinel message handlers


void c_dlg_msr_sentinel::OnBnClickedButtonApply()
{
	// TODO: Add your control notification handler code here
}


void c_dlg_msr_sentinel::OnBnClickedButtonRestoreDefault()
{
	// TODO: Add your control notification handler code here
}
