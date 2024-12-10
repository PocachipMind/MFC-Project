
// 00_timerSampleView.cpp: CMy00timerSampleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "00_timerSample.h"
#endif

#include "00_timerSampleDoc.h"
#include "00_timerSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy00timerSampleView

IMPLEMENT_DYNCREATE(CMy00timerSampleView, CView)

BEGIN_MESSAGE_MAP(CMy00timerSampleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_TIMER_SET, &CMy00timerSampleView::OnTimerSet)
	ON_COMMAND(ID_TIMER_KILL, &CMy00timerSampleView::OnTimerKill)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMy00timerSampleView 생성/소멸

CMy00timerSampleView::CMy00timerSampleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy00timerSampleView::~CMy00timerSampleView()
{
}

BOOL CMy00timerSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy00timerSampleView 그리기

void CMy00timerSampleView::OnDraw(CDC* /*pDC*/)
{
	CMy00timerSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy00timerSampleView 인쇄

BOOL CMy00timerSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy00timerSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy00timerSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy00timerSampleView 진단

#ifdef _DEBUG
void CMy00timerSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMy00timerSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy00timerSampleDoc* CMy00timerSampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy00timerSampleDoc)));
	return (CMy00timerSampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy00timerSampleView 메시지 처리기


void CMy00timerSampleView::OnTimerSet()
{
	SetTimer(5, 1000, NULL);
}


void CMy00timerSampleView::OnTimerKill()
{
	KillTimer(5);
}


void CMy00timerSampleView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 5)
	{
		static int counter = 0;
		RedrawWindow();
		CClientDC dc(this);
		CString strTmp;
		strTmp.Format(_T("Counter: %d"), counter++);
		dc.TextOut(10, 10, strTmp);

		//Sleep(2000);
	}

	CView::OnTimer(nIDEvent);
}
