
// 06_threadAndUiView.cpp: CMy06threadAndUiView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "06_threadAndUi.h"
#endif

#include "06_threadAndUiDoc.h"
#include "06_threadAndUiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy06threadAndUiView

IMPLEMENT_DYNCREATE(CMy06threadAndUiView, CView)

BEGIN_MESSAGE_MAP(CMy06threadAndUiView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_COMMAND(ID_DIALOG_SHOW, &CMy06threadAndUiView::OnDialogShow)
	ON_COMMAND(ID_DIALOG_SETDATA, &CMy06threadAndUiView::OnDialogSetdata)
	ON_COMMAND(ID_DIALOG_USERMESSAGE, &CMy06threadAndUiView::OnDialogUsermessage)
	ON_MESSAGE(UM_SETDATA, OnUmSetData)
END_MESSAGE_MAP()

// CMy06threadAndUiView 생성/소멸

CMy06threadAndUiView::CMy06threadAndUiView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy06threadAndUiView::~CMy06threadAndUiView()
{
}

BOOL CMy06threadAndUiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy06threadAndUiView 그리기

void CMy06threadAndUiView::OnDraw(CDC* /*pDC*/)
{
	CMy06threadAndUiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy06threadAndUiView 인쇄

BOOL CMy06threadAndUiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy06threadAndUiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy06threadAndUiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy06threadAndUiView 진단

#ifdef _DEBUG
void CMy06threadAndUiView::AssertValid() const
{
	CView::AssertValid();
}

void CMy06threadAndUiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy06threadAndUiDoc* CMy06threadAndUiView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06threadAndUiDoc)));
	return (CMy06threadAndUiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy06threadAndUiView 메시지 처리기


int CMy06threadAndUiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndInfo.Create(IDD_DIALOG_INFO);

	return 0;
}

void CMy06threadAndUiView::OnDialogShow()
{
	m_wndInfo.ShowWindow(SW_SHOW);
}

UINT ThreadSetData(LPVOID pParam)
{
	CMy06threadAndUiView* pView = (CMy06threadAndUiView*)pParam;
	for (int i = 0; i < 10; ++i)
	{
		pView->m_wndInfo.SetData(i);
		Sleep(500);
	}
	return 0;
}

void CMy06threadAndUiView::OnDialogSetdata()
{
	AfxBeginThread(ThreadSetData, this);
}


LRESULT CMy06threadAndUiView::OnUmSetData(WPARAM wParam, LPARAM lParam)
{
	m_wndInfo.SetData((int)wParam);
	return 0;
}

UINT ThreadSendUserMsg(LPVOID pParam)
{
	CMy06threadAndUiView* pView = (CMy06threadAndUiView*)pParam;
	for (int i = 0; i <= 10; ++i)
	{
		pView->PostMessage(UM_SETDATA, i, 0);
		Sleep(500);
	}
	return 0;
}

void CMy06threadAndUiView::OnDialogUsermessage()
{
	AfxBeginThread(ThreadSendUserMsg, this);
}

