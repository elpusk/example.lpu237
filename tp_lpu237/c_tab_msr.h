#pragma once
#include <memory>

#include "c_dlg_msr_sentinel.h"

// c_tab_msr dialog

class c_tab_msr : public CDialogEx
{
	DECLARE_DYNAMIC(c_tab_msr)

public:
	typedef	std::shared_ptr<c_tab_msr>	type_ptr;

public:
	c_tab_msr(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_tab_msr();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MSR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMsrConfig();
	afx_msg void OnBnClickedButtonMsrSentinels();
};
