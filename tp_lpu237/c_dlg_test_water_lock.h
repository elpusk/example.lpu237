#pragma once


// c_dlg_test_water_lock dialog

class c_dlg_test_water_lock : public CDialogEx
{
	DECLARE_DYNAMIC(c_dlg_test_water_lock)

public:
	c_dlg_test_water_lock(CWnd* pParent = nullptr);   // standard constructor
	virtual ~c_dlg_test_water_lock();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST_SUB_WATER_LOCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_static_state;
	CStatic m_static_serial_number;
};
