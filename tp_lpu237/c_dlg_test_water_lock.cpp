// c_dlg_test_water_lock.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_test_water_lock.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(c_dlg_test_water_lock, CDialogEx)
END_MESSAGE_MAP()


// c_dlg_test_water_lock message handlers
