// c_dlg_msr_test.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "c_dlg_msr_test.h"
#include "afxdialogex.h"


// c_dlg_msr_test dialog

IMPLEMENT_DYNAMIC(c_dlg_msr_test, CDialogEx)

c_dlg_msr_test::c_dlg_msr_test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPOS_SUB_MSR, pParent), m_b_open(false)
{

}

c_dlg_msr_test::~c_dlg_msr_test()
{
}

void c_dlg_msr_test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPOSMSR, m_OposMsr);
	DDX_Control(pDX, IDC_LIST_INFO, m_listbox_info);
}


BEGIN_MESSAGE_MAP(c_dlg_msr_test, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// c_dlg_msr_test message handlers


BOOL c_dlg_msr_test::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_b_open = _open_opos_msr();

	if (!m_b_open) {
		AfxMessageBox(L"ERROR : open opos msr.");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void c_dlg_msr_test::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
}


void c_dlg_msr_test::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
}

void c_dlg_msr_test::info(const std::wstring& s_info)
{
	if (m_listbox_info.GetCount() > 500)
		m_listbox_info.ResetContent();

	m_listbox_info.AddString(s_info.c_str());
	m_listbox_info.SetCurSel(m_listbox_info.GetCount() - 1);

}

bool c_dlg_msr_test::_open_opos_msr()
{
	bool b_result(false);

	do {
		long l_result = m_OposMsr.Open(L"Lpu230MSR");

		if (l_result != OPOS_SUCCESS) {
			continue;
		}

		l_result = m_OposMsr.ClaimDevice(2000);

		if (l_result != OPOS_SUCCESS) {
			continue;
		}
		m_OposMsr.put_DeviceEnabled(TRUE);
		m_OposMsr.put_DataEventEnabled(TRUE);
		//m_OposMsr.get_DataEventEnabled()
		//m_OposMsr.get_DeviceEnabled()
		m_OposMsr.put_FreezeEvents(FALSE);

		//
		if (!m_OposMsr.get_DeviceEnabled()) {
			ATLTRACE(L"get_DeviceEnabled : DISABLE");
		}
		if (!m_OposMsr.get_DataEventEnabled()) {
			ATLTRACE(L"get_DataEventEnabled : DISABLE");
		}
		if (m_OposMsr.get_FreezeEvents()) {
			ATLTRACE(L"get_FreezeEvents : ENABLE");
		}

		//m_OposMsr.get_TracksToRead() - return MSR_TR_1_2_3 and so on.
		m_OposMsr.put_TracksToRead(MSR_TR_1_2_3);

		//m_OposMsr.get_TransmitSentinels()
		m_OposMsr.put_TransmitSentinels(TRUE);

		//m_OposMsr.get_ErrorReportingType() - MSR_ERT_CARD or MSR_ERT_TRACK
		m_OposMsr.put_ErrorReportingType(MSR_ERT_CARD);
		//
		b_result = true;
	} while (false);

	return b_result;
}

BEGIN_EVENTSINK_MAP(c_dlg_msr_test, CDialogEx)
	ON_EVENT(c_dlg_msr_test, IDC_OPOSMSR, 1, c_dlg_msr_test::DataEventOposmsr, VTS_I4)
	ON_EVENT(c_dlg_msr_test, IDC_OPOSMSR, 2, c_dlg_msr_test::DirectIOEventOposmsr, VTS_I4 VTS_PI4 VTS_PBSTR)
	ON_EVENT(c_dlg_msr_test, IDC_OPOSMSR, 3, c_dlg_msr_test::ErrorEventOposmsr, VTS_I4 VTS_I4 VTS_I4 VTS_PI4)
	ON_EVENT(c_dlg_msr_test, IDC_OPOSMSR, 5, c_dlg_msr_test::StatusUpdateEventOposmsr, VTS_I4)
END_EVENTSINK_MAP()


void c_dlg_msr_test::DataEventOposmsr(long Status)
{
	CString stemp;
	bool bGood = true;
	long lTrackToRead = MSR_TR_1_2_3;

	WORD wH = HIWORD(Status);
	WORD wL = LOWORD(Status);

	char cError[3];

	cError[0] = LOBYTE(wL);
	cError[1] = HIBYTE(wL);
	cError[2] = LOBYTE(wH);

	stemp.Format(L"=============================================");
	info((LPCTSTR)stemp);

	//stemp.Format(L" %d. Data Event : ISO1 = %d, ISO2 = %d, ISO3 = %d", m_nTotal + 1, cError[0], cError[1], cError[2]);
	stemp.Format(L" Data Event : ISO1 = %d, ISO2 = %d, ISO3 = %d", cError[0], cError[1], cError[2]);
	info((LPCTSTR)stemp);

	if (!m_OposMsr.get_Track1Data().IsEmpty()) {
		stemp.Format(L"CARD = %s", m_OposMsr.get_Track1Data());
	}
	else {
		stemp.Format(L"ISO1 - LEN 0");

		lTrackToRead = m_OposMsr.get_TracksToRead();
		if (lTrackToRead & MSR_TR_1)
			bGood = false;
	}
	info((LPCTSTR)stemp);

	if (!m_OposMsr.get_Track2Data().IsEmpty()) {
		stemp.Format(L"CARD = %s", m_OposMsr.get_Track2Data());
	}
	else {
		stemp.Format(L"ISO2 - LEN 0");

		lTrackToRead = m_OposMsr.get_TracksToRead();
		if (lTrackToRead & MSR_TR_2)

			bGood = false;
	}
	info((LPCTSTR)stemp);

	if (!m_OposMsr.get_Track3Data().IsEmpty()) {
		stemp.Format(L"CARD = %s", m_OposMsr.get_Track3Data());
	}
	else {
		stemp.Format(L"ISO3 - LEN 0");

		lTrackToRead = m_OposMsr.get_TracksToRead();
		if (lTrackToRead & MSR_TR_3)

			bGood = false;
	}
	info((LPCTSTR)stemp);

	/*
	if (bGood)
		m_nGood++;
	else
		m_nBad++;

	m_nTotal = m_nGood + m_nBad;

	stemp.Format(L"%d", m_nGood);
	m_EditGood.SetWindowText(stemp);

	stemp.Format(L"%d", m_nBad);
	m_EditBad.SetWindowText(stemp);

	stemp.Format(L"%d", m_nTotal);
	m_EditTotal.SetWindowText(stemp);
	*/

	m_OposMsr.put_DataEventEnabled(TRUE);
}

void c_dlg_msr_test::DirectIOEventOposmsr(long EventNumber, long* pData, BSTR* pString)
{
}


void c_dlg_msr_test::ErrorEventOposmsr(long ResultCode, long ResultCodeExtended, long ErrorLocus, long* pErrorResponse)
{
	CString stemp;

	stemp.Format(L"=============================================");
	info((LPCTSTR)stemp);

	//stemp.Format(L" %d. ERROR EVENT : ResultCode = %d, ResultCodeExtended = 0x%08x, ErrorLocus = %d", m_nTotal + 1, ResultCode, ResultCodeExtended, ErrorLocus);
	stemp.Format(L" ERROR EVENT : ResultCode = %d, ResultCodeExtended = 0x%08x, ErrorLocus = %d", ResultCode, ResultCodeExtended, ErrorLocus);
	info((LPCTSTR)stemp);

	bool bGood = true;

	WORD wH = HIWORD(ResultCodeExtended);
	WORD wL = LOWORD(ResultCodeExtended);

	char cError[3];

	cError[0] = LOBYTE(wL);
	cError[1] = HIBYTE(wL);
	cError[2] = LOBYTE(wH);

	stemp.Format(L"ERROR Event : ISO1 = %d, ISO2 = %d, ISO3 = %d", cError[0], cError[1], cError[2]);
	info((LPCTSTR)stemp);

	if (!m_OposMsr.get_Track1Data().IsEmpty()) {
		stemp.Format(L"CARD = %s", m_OposMsr.get_Track1Data());
	}
	else {
		stemp.Format(L"ISO1 - LEN 0");
		bGood = false;
	}
	info((LPCTSTR)stemp);

	if (!m_OposMsr.get_Track2Data().IsEmpty()) {
		stemp.Format(L"CARD = %s", m_OposMsr.get_Track2Data());
	}
	else {
		stemp.Format(L"ISO2 - LEN 0");
		bGood = false;
	}
	info((LPCTSTR)stemp);

	if (!m_OposMsr.get_Track3Data().IsEmpty()) {
		stemp.Format(L"CARD = %s", m_OposMsr.get_Track3Data());
	}
	else {
		stemp.Format(L"ISO3 - LEN 0");
		bGood = false;
	}
	info((LPCTSTR)stemp);
	/*
	if (bGood)
		m_nGood++;
	else
		m_nBad++;

	m_nTotal = m_nGood + m_nBad;

	stemp.Format(L"%d", m_nGood);
	m_EditGood.SetWindowText(stemp);

	stemp.Format(L"%d", m_nBad);
	m_EditBad.SetWindowText(stemp);

	stemp.Format(L"%d", m_nTotal);
	m_EditTotal.SetWindowText(stemp);
	*/

	m_OposMsr.put_DataEventEnabled(TRUE);
}


void c_dlg_msr_test::StatusUpdateEventOposmsr(long Data)
{
}


void c_dlg_msr_test::OnClose()
{
	do {
		if (!m_b_open)
			continue;
		long l_result = m_OposMsr.ReleaseDevice();
		if (l_result != OPOS_SUCCESS) {
			ATLTRACE(L"Error");
		}

		l_result = m_OposMsr.Close();

		if (l_result != OPOS_SUCCESS) {
			ATLTRACE(L"Error");
		}

	} while (false);

	CDialogEx::OnClose();
}
