#pragma once

#include <string>
#include "opos/OposMsr.h"
#include "oposmsr_ocx.h"
// c_dlg_msr_test dialog

class c_dlg_msr_test : public CDialogEx
{
	DECLARE_DYNAMIC(c_dlg_msr_test)

public:
	c_dlg_msr_test(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_dlg_msr_test();

private:
	bool _open_opos_msr();
private:
	bool m_b_open;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPOS_SUB_MSR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listbox_info;
	void info(const std::wstring& s_info);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();

	COposmsr m_OposMsr;
	DECLARE_EVENTSINK_MAP()
	void DataEventOposmsr(long Status);
	void DirectIOEventOposmsr(long EventNumber, long* pData, BSTR* pString);
	void ErrorEventOposmsr(long ResultCode, long ResultCodeExtended, long ErrorLocus, long* pErrorResponse);
	void StatusUpdateEventOposmsr(long Data);
	afx_msg void OnClose();
};
