#pragma once
#include <memory>

#include "c_dlg_msr_test.h"

// c_tab_opos dialog

class c_tab_opos : public CDialogEx
{
	DECLARE_DYNAMIC(c_tab_opos)

public:
	typedef	std::shared_ptr<c_tab_opos>	type_ptr;

public:
	c_tab_opos(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_tab_opos();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPOS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOposMsr();
};
