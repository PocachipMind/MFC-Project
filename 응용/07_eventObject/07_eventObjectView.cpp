
// 07_eventObjectView.cpp: CMy07eventObjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "07_eventObject.h"
#endif

#include "07_eventObjectDoc.h"
#include "07_eventObjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy07eventObjectView

IMPLEMENT_DYNCREATE(CMy07eventObjectView, CView)

BEGIN_MESSAGE_MAP(CMy07eventObjectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EVENT_THREAD, &CMy07eventObjectView::OnEventThread)
	ON_COMMAND(ID_EVENT_SET, &CMy07eventObjectView::OnEventSet)
	ON_COMMAND(ID_EVENT_RESET, &CMy07eventObjectView::OnEventReset)
END_MESSAGE_MAP()

// CMy07eventObjectView 생성/소멸

CMy07eventObjectView::CMy07eventObjectView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy07eventObjectView::~CMy07eventObjectView()
{
}

BOOL CMy07eventObjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy07eventObjectView 그리기

void CMy07eventObjectView::OnDraw(CDC* /*pDC*/)
{
	CMy07eventObjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy07eventObjectView 인쇄

BOOL CMy07eventObjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy07eventObjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy07eventObjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy07eventObjectView 진단

#ifdef _DEBUG
void CMy07eventObjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMy07eventObjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy07eventObjectDoc* CMy07eventObjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy07eventObjectDoc)));
	return (CMy07eventObjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy07eventObjectView 메시지 처리기


CEvent g_evtExit(FALSE, TRUE, _T("TEST_EXIT_EVENT"));

UINT ThreadWaitForEvent(LPVOID pParam)
{
	CString strTmp;
	strTmp.Format(_T("%d: ThreadWaitForEvent() - Begin\n"), pParam);
	OutputDebugString(strTmp);

	while (WaitForSingleObject(g_evtExit.m_hObject, 1) == WAIT_TIMEOUT);

	strTmp.Format(_T("%d: ThreadWaitForEvent() - End\n"), pParam);
	OutputDebugString(strTmp);
	return 0;
}

void CMy07eventObjectView::OnEventThread()
{
	for(long long i = 0; i < 5; ++i)
		AfxBeginThread(ThreadWaitForEvent, (LPVOID)i);
}

void CMy07eventObjectView::OnEventSet()
{
	g_evtExit.SetEvent();
	::Sleep(200);
}

void CMy07eventObjectView::OnEventReset()
{
	g_evtExit.ResetEvent();
}
