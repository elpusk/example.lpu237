// cprogress.cpp : implementation file
//

#include "pch.h"
#include "tp_lpu237.h"
#include "cprogress.h"
#include "afxdialogex.h"


// cprogress dialog

IMPLEMENT_DYNAMIC(cprogress, CDialogEx)

cprogress::cprogress(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROGRESS, pParent)
{

}

cprogress::~cprogress()
{
}

void cprogress::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_PROCESS, m_progress_process);
}


BEGIN_MESSAGE_MAP(cprogress, CDialogEx)
	ON_MESSAGE(_exam::const_wnd_msg_get_parameter, on_get_parameter)
	ON_MESSAGE(_exam::const_wnd_msg_set_parameter, on_set_parameter)
END_MESSAGE_MAP()


// cprogress message handlers

LRESULT cprogress::on_get_parameter(WPARAM wParam, LPARAM lParam)
{
	DWORD dw_current_step_result(wParam);
	DWORD dw_zero_base_current_step(_exam::cmgmt_lpu237::get_step_index_from_lparam(lParam));
	DWORD dw_total_step(_exam::cmgmt_lpu237::get_total_step_from_lparam(lParam));

	m_progress_process.SetRange(0, dw_total_step);
	m_progress_process.SetPos(dw_zero_base_current_step + 1);

	if (dw_current_step_result == LPU237_TOOLS_RESULT_SUCCESS) {
		ATLTRACE(L"SUCCESS : %u/%u.\n", dw_zero_base_current_step + 1, dw_total_step);
		if (dw_total_step == dw_zero_base_current_step + 1) {
			EndDialog(0);
		}

	}
	else {
		ATLTRACE(L"ERROR : %u/%u.\n", dw_zero_base_current_step + 1, dw_total_step);
		EndDialog(0);
	}

	//
	return 0;
}

LRESULT cprogress::on_set_parameter(WPARAM wParam, LPARAM lParam)
{
	DWORD dw_current_step_result(wParam);
	DWORD dw_zero_base_current_step(_exam::cmgmt_lpu237::get_step_index_from_lparam(lParam));
	DWORD dw_total_step(_exam::cmgmt_lpu237::get_total_step_from_lparam(lParam));

	m_progress_process.SetRange(0, dw_total_step);
	m_progress_process.SetPos(dw_zero_base_current_step + 1);

	if (dw_current_step_result == LPU237_TOOLS_RESULT_SUCCESS) {
		ATLTRACE(L"SUCCESS : %u/%u.\n", dw_zero_base_current_step + 1, dw_total_step);
		if (dw_total_step == dw_zero_base_current_step + 1) {
			EndDialog(0);
		}

	}
	else {
		ATLTRACE(L"ERROR : %u/%u.\n", dw_zero_base_current_step + 1, dw_total_step);
		EndDialog(0);
	}

	//
	return 0;
}

BOOL cprogress::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_exam::cmgmt_lpu237& mgmt(_exam::cmgmt_lpu237::get_instance());

	m_progress_process.SetRange(0, 100);

	if (m_b_save) {
		SetWindowText(L"Saving");
		if (!mgmt.start_save_parameter(m_hWnd, _exam::const_wnd_msg_set_parameter)) {
			AfxMessageBox(L"fail : starts a saving parameter.");
			EndDialog(0);
		}
	}
	else {
		SetWindowText(L"Loading");
		if (!mgmt.start_load_parameter(m_hWnd, _exam::const_wnd_msg_get_parameter)) {
			AfxMessageBox(L"fail : starts a loading parameter.");
			EndDialog(0);
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
