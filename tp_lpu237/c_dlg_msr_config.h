#pragma once


// c_dlg_msr_config dialog

class c_dlg_msr_config : public CDialogEx
{
	DECLARE_DYNAMIC(c_dlg_msr_config)

public:
	c_dlg_msr_config(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_dlg_msr_config();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MSR_SUB_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_port_type;
	CComboBox m_combo_interface_type;
	CComboBox m_combo_buzzer;
	CComboBox m_combo_keyboard_language;
};
