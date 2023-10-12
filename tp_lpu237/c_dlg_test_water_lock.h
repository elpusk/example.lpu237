#pragma once

#include "_exm_mgmt_lpu237.h"

// c_dlg_test_water_lock dialog

class c_dlg_test_water_lock : public CDialogEx
{
	DECLARE_DYNAMIC(c_dlg_test_water_lock)

public:
	c_dlg_test_water_lock(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_dlg_test_water_lock();

private:
	bool is_exit();

private:
	std::wstring m_s_old_interface;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_SUB_WATER_LOCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT on_get_ibutton(WPARAM wParam, LPARAM lParam);
public:
	CStatic m_static_state;
	CStatic m_static_serial_number;
	CComboBox m_combo_ibutton_type;
	CEdit m_edit_start_sentinel;
	CEdit m_edit_stop_sentinel;
	CEdit m_edit_port_type;
	CEdit m_edit_interface_port;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboIbuttonType();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CComboBox m_combo_start;
	CComboBox m_combo_end;
	afx_msg void OnCbnSelchangeComboStart();
	afx_msg void OnCbnSelchangeComboEnd();
};
