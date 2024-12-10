
// 01_timerPumpView.cpp: CMy01timerPumpView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "01_timerPump.h"
#endif

#include "01_timerPumpDoc.h"
#include "01_timerPumpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy01timerPumpView

IMPLEMENT_DYNCREATE(CMy01timerPumpView, CView)

BEGIN_MESSAGE_MAP(CMy01timerPumpView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_COUNTER, &CMy01timerPumpView::OnTestCounter)
END_MESSAGE_MAP()

// CMy01timerPumpView 생성/소멸

CMy01timerPumpView::CMy01timerPumpView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy01timerPumpView::~CMy01timerPumpView()
{
}

BOOL CMy01timerPumpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy01timerPumpView 그리기

void CMy01timerPumpView::OnDraw(CDC* /*pDC*/)
{
	CMy01timerPumpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy01timerPumpView 인쇄

BOOL CMy01timerPumpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy01timerPumpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy01timerPumpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy01timerPumpView 진단

#ifdef _DEBUG
void CMy01timerPumpView::AssertValid() const
{
	CView::AssertValid();
}

void CMy01timerPumpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy01timerPumpDoc* CMy01timerPumpView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy01timerPumpDoc)));
	return (CMy01timerPumpDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy01timerPumpView 메시지 처리기


void CMy01timerPumpView::OnTestCounter()
{
	CClientDC dc(this);
	CString strTmp;
	for (int i = 0; i < 500; ++i)
	{
		RedrawWindow();
		strTmp.Format(_T("Counter: %d"), i);
		dc.TextOut(10, 10, strTmp);
		Sleep(1);
		PeekAndPump();
	}
}


BOOL CMy01timerPumpView::PeekAndPump()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage()) {
			::PostQuitMessage(0);
			return FALSE;
		}
	}

	return TRUE;
}
