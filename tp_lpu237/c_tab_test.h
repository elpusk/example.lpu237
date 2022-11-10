#pragma once

#include <memory>

#include "c_dlg_test_water_lock.h"

// c_tab_test dialog

class c_tab_test : public CDialogEx
{
	DECLARE_DYNAMIC(c_tab_test)

public:
	typedef	std::shared_ptr<c_tab_test>	type_ptr;

public:
	c_tab_test(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_tab_test();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTestWaterLock();
};
