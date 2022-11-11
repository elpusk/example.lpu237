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
	DDX_Control(pDX, IDC_CHECK_ISO1, m_check_enable_iso[0]);
	DDX_Control(pDX, IDC_CHECK_ISO2, m_check_enable_iso[1]);
	DDX_Control(pDX, IDC_CHECK_ISO3, m_check_enable_iso[2]);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_sentinel, CDialogEx)
END_MESSAGE_MAP()


// c_dlg_msr_sentinel message handlers
