#pragma once


// c_dlg_msr_sentinel dialog

class c_dlg_msr_sentinel : public CDialogEx
{
	DECLARE_DYNAMIC(c_dlg_msr_sentinel)

public:
	c_dlg_msr_sentinel(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_dlg_msr_sentinel();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MSR_SUB_SENTINELS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_iso1_start_sentinel[3];
	CEdit m_edit_iso1_end_sentinel[3];
	CButton m_check_enable_iso[3];
};
