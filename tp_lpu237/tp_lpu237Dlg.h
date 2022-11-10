
// tp_lpu237Dlg.h : header file
//

#pragma once

#include "c_tab_msr.h"
#include "c_tab_opos.h"
#include "c_tab_test.h"

// Ctplpu237Dlg dialog
class Ctplpu237Dlg : public CDialogEx
{

private:
	enum : int {
		CINDEX_OPOS = 0,
		CINDEX_MSR,
		CINDEX_TEST,
		CINDEX_LAST //this value must be last memnber always.
	};
// Construction
public:
	Ctplpu237Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TP_LPU237_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;

private:
	c_tab_msr::type_ptr m_ptr_tab_msr;
	c_tab_opos::type_ptr m_ptr_tab_opos;
	c_tab_test::type_ptr m_ptr_tab_test;
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
};
