
// tp_lpu237Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "tp_lpu237.h"
#include "tp_lpu237Dlg.h"
#include "afxdialogex.h"

#include "_exm_mgmt_lpu237.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctplpu237Dlg dialog



Ctplpu237Dlg::Ctplpu237Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TP_LPU237_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctplpu237Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
}

BEGIN_MESSAGE_MAP(Ctplpu237Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &Ctplpu237Dlg::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// Ctplpu237Dlg message handlers

BOOL Ctplpu237Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_tab.InsertItem(CINDEX_OPOS, L"  OPOS  ");
	m_tab.InsertItem(CINDEX_MSR, L"  MSR  ");
	m_tab.InsertItem(CINDEX_TEST, L"  TEST  ");

	m_tab.SetCurSel(CINDEX_OPOS);

	CRect rc;
	m_tab.GetWindowRect(&rc);

	int x(0), y(20);
	m_ptr_tab_opos = c_tab_opos::type_ptr(new c_tab_opos());
	m_ptr_tab_opos->Create(IDD_DIALOG_OPOS, &m_tab);
	m_ptr_tab_opos->MoveWindow(x, y, rc.Width(), rc.Height());
	m_ptr_tab_opos->ShowWindow(SW_SHOW);

	m_ptr_tab_msr = c_tab_msr::type_ptr(new c_tab_msr());
	m_ptr_tab_msr->Create(IDD_DIALOG_MSR, &m_tab);
	m_ptr_tab_msr->MoveWindow(x, y, rc.Width(), rc.Height());
	m_ptr_tab_msr->ShowWindow(SW_HIDE);

	m_ptr_tab_test = c_tab_test::type_ptr(new c_tab_test());
	m_ptr_tab_test->Create(IDD_DIALOG_TEST, &m_tab);
	m_ptr_tab_test->MoveWindow(x, y, rc.Width(), rc.Height());
	m_ptr_tab_test->ShowWindow(SW_HIDE);

	//
	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	do {
		if (!mgmt.load_dll()) {
			AfxMessageBox(L"component dll isn't.");
			continue;
		}
		if (!mgmt.select_the_first_device().first) {
			AfxMessageBox(L"Please connects a MSR device. and restart program.");
			continue;
		}
		
		ATLTRACE(L" success : mgmt. \n");

	}while(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ctplpu237Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ctplpu237Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctplpu237Dlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	int n_sel = m_tab.GetCurSel();

	switch (n_sel) 
	{
	case CINDEX_OPOS:
		m_ptr_tab_opos->ShowWindow(SW_SHOW);
		m_ptr_tab_msr->ShowWindow(SW_HIDE);
		m_ptr_tab_test->ShowWindow(SW_HIDE);
		break;
	case CINDEX_MSR:
		m_ptr_tab_opos->ShowWindow(SW_HIDE);
		m_ptr_tab_msr->ShowWindow(SW_SHOW);
		m_ptr_tab_test->ShowWindow(SW_HIDE);
		break;
	case CINDEX_TEST:
		m_ptr_tab_opos->ShowWindow(SW_HIDE);
		m_ptr_tab_msr->ShowWindow(SW_HIDE);
		m_ptr_tab_test->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}//end switch



	//
	*pResult = 0;
}
