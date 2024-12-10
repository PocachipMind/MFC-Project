
// 10_mutexSampleView.cpp: CMy10mutexSampleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "10_mutexSample.h"
#endif

#include "10_mutexSampleDoc.h"
#include "10_mutexSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy10mutexSampleView

IMPLEMENT_DYNCREATE(CMy10mutexSampleView, CView)

BEGIN_MESSAGE_MAP(CMy10mutexSampleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_MUTEX_LOCK, &CMy10mutexSampleView::OnMutexLock)
	ON_COMMAND(ID_MUTEX_UNLOCK, &CMy10mutexSampleView::OnMutexUnlock)
END_MESSAGE_MAP()

// CMy10mutexSampleView 생성/소멸

CMy10mutexSampleView::CMy10mutexSampleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy10mutexSampleView::~CMy10mutexSampleView()
{
}

BOOL CMy10mutexSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy10mutexSampleView 그리기

void CMy10mutexSampleView::OnDraw(CDC* /*pDC*/)
{
	CMy10mutexSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy10mutexSampleView 인쇄

BOOL CMy10mutexSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy10mutexSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy10mutexSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy10mutexSampleView 진단

#ifdef _DEBUG
void CMy10mutexSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMy10mutexSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy10mutexSampleDoc* CMy10mutexSampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy10mutexSampleDoc)));
	return (CMy10mutexSampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy10mutexSampleView 메시지 처리기

CMutex g_mtx(FALSE, _T("MUTEX_TEST_OBJ"));

void CMy10mutexSampleView::OnMutexLock()
{
	CString strTmp;
	if (g_mtx.Lock(500))
		strTmp.Format(_T("**PID: %d, Exclusive access. (Lock)**\n"),
			::GetCurrentProcessId());
	else
		strTmp.Format(_T("PID: %d, Timeout!\n"), ::GetCurrentProcessId());

	OutputDebugString(strTmp);
}


void CMy10mutexSampleView::OnMutexUnlock()
{
	CString strTmp;
	g_mtx.Unlock();

	strTmp.Format(_T("PID: %d, Unlock()\n"), ::GetCurrentProcessId());
	OutputDebugString(strTmp);
}
