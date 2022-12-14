// c_tab_test.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_tab_test.h"
#include "afxdialogex.h"

#include "_exm_mgmt_lpu237.h"

// c_tab_test dialog

IMPLEMENT_DYNAMIC(c_tab_test, CDialogEx)

c_tab_test::c_tab_test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEST, pParent)
{

}

c_tab_test::~c_tab_test()
{
}

void c_tab_test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(c_tab_test, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEST_WATER_LOCK, &c_tab_test::OnBnClickedButtonTestWaterLock)
END_MESSAGE_MAP()


// c_tab_test message handlers


void c_tab_test::OnBnClickedButtonTestWaterLock()
{
	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	do {
		if (!mgmt.is_selected_device()) {
			AfxMessageBox(L" ERROR : not selected device.");
			continue;
		}
		if (!mgmt.is_support_ibutton()) {
			AfxMessageBox(L" ERROR : the current device dosen't support ibutton-reading");
			continue;
		}

		c_dlg_test_water_lock dlg;
		dlg.DoModal();
	} while (false);

}
