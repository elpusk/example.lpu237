// c_dlg_msr_test.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_msr_test.h"
#include "afxdialogex.h"


// c_dlg_msr_test dialog

IMPLEMENT_DYNAMIC(c_dlg_msr_test, CDialogEx)

c_dlg_msr_test::c_dlg_msr_test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPOS_SUB_MSR, pParent)
{

}

c_dlg_msr_test::~c_dlg_msr_test()
{
}

void c_dlg_msr_test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_listbox_info);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_test, CDialogEx)
END_MESSAGE_MAP()


// c_dlg_msr_test message handlers
