// CInfoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "06_threadAndUi.h"
#include "afxdialogex.h"
#include "CInfoDlg.h"


// CInfoDlg 대화 상자

IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
	, m_strData(_T(""))
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Static_Data, m_strData);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CInfoDlg 메시지 처리기


void CInfoDlg::SetData(int param)
{
	if (param == 10)
	{
		ShowWindow(SW_HIDE);
		return;
	}

	m_strData.Format(_T("%d"), param);
	UpdateData(FALSE);
}
