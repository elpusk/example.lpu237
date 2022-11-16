#pragma once
#include "_exm_mgmt_lpu237.h"

// cprogress dialog

class cprogress : public CDialogEx
{
	DECLARE_DYNAMIC(cprogress)

public:
	cprogress & set_save_mode( bool b_save = true)
	{
		m_b_save = b_save;
		return *this;
	}
	cprogress(CWnd* pParent = nullptr);   // standard constructor
	virtual ~cprogress();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROGRESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT on_get_parameter(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT on_set_parameter(WPARAM wParam, LPARAM lParam);
public:
	CProgressCtrl m_progress_process;
	virtual BOOL OnInitDialog();

private:
	bool m_b_save;
};
