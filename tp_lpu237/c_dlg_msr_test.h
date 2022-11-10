#pragma once


// c_dlg_msr_test dialog

class c_dlg_msr_test : public CDialogEx
{
	DECLARE_DYNAMIC(c_dlg_msr_test)

public:
	c_dlg_msr_test(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_dlg_msr_test();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPOS_SUB_MSR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listbox_info;
};
