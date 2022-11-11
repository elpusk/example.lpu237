// c_dlg_msr_config.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_msr_config.h"
#include "afxdialogex.h"


// c_dlg_msr_config dialog

IMPLEMENT_DYNAMIC(c_dlg_msr_config, CDialogEx)

c_dlg_msr_config::c_dlg_msr_config(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MSR_SUB_CONFIG, pParent)
{

}

c_dlg_msr_config::~c_dlg_msr_config()
{
}

void c_dlg_msr_config::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT_TYPE, m_combo_port_type);
	DDX_Control(pDX, IDC_COMBO_INTERFACE_PORT, m_combo_interface_type);
	DDX_Control(pDX, IDC_COMBO_BUZZER, m_combo_buzzer);
	DDX_Control(pDX, IDC_COMBO_KEYBOARD_LANGUAGE, m_combo_keyboard_language);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_config, CDialogEx)
END_MESSAGE_MAP()


// c_dlg_msr_config message handlers
