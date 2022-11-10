// c_tab_opos.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_tab_opos.h"
#include "afxdialogex.h"


// c_tab_opos dialog

IMPLEMENT_DYNAMIC(c_tab_opos, CDialogEx)

c_tab_opos::c_tab_opos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPOS, pParent)
{

}

c_tab_opos::~c_tab_opos()
{
}

void c_tab_opos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(c_tab_opos, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPOS_MSR, &c_tab_opos::OnBnClickedButtonOposMsr)
END_MESSAGE_MAP()


// c_tab_opos message handlers


void c_tab_opos::OnBnClickedButtonOposMsr()
{
	c_dlg_msr_test dlg;

	dlg.DoModal();
}
