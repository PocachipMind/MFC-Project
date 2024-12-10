
// 04_threadCtrlView.cpp: CMy04threadCtrlView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "04_threadCtrl.h"
#endif

#include "04_threadCtrlDoc.h"
#include "04_threadCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy04threadCtrlView

IMPLEMENT_DYNCREATE(CMy04threadCtrlView, CView)

BEGIN_MESSAGE_MAP(CMy04threadCtrlView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_SUSPENDED, &CMy04threadCtrlView::OnThreadSuspended)
	ON_COMMAND(ID_THREAD_RESUME, &CMy04threadCtrlView::OnThreadResume)
	ON_COMMAND(ID_THREAD_SUSPEND, &CMy04threadCtrlView::OnThreadSuspend)
	ON_COMMAND(ID_THREAD_TERMINATE, &CMy04threadCtrlView::OnThreadTerminate)
	ON_COMMAND(ID_THREAD_EXIT, &CMy04threadCtrlView::OnThreadExit)
END_MESSAGE_MAP()

// CMy04threadCtrlView 생성/소멸

CMy04threadCtrlView::CMy04threadCtrlView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy04threadCtrlView::~CMy04threadCtrlView()
{
}

BOOL CMy04threadCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy04threadCtrlView 그리기

void CMy04threadCtrlView::OnDraw(CDC* /*pDC*/)
{
	CMy04threadCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy04threadCtrlView 인쇄

BOOL CMy04threadCtrlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy04threadCtrlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy04threadCtrlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy04threadCtrlView 진단

#ifdef _DEBUG
void CMy04threadCtrlView::AssertValid() const
{
	CView::AssertValid();
}

void CMy04threadCtrlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy04threadCtrlDoc* CMy04threadCtrlView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy04threadCtrlDoc)));
	return (CMy04threadCtrlDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy04threadCtrlView 메시지 처리기

BOOL g_bExit = FALSE;

UINT ThreadTest03(LPVOID pParam)
{
	OutputDebugString(_T("ThreadTest03() - Begin\n"));
	while(!g_bExit)
	{
		OutputDebugString(_T("ThreadTest03() - while\n"));
		Sleep(1000);
	}
	OutputDebugString(_T("ThreadTest03() - End\n"));
	return 0;
}

void CMy04threadCtrlView::OnThreadSuspended()
{
	if (m_pThread != NULL)
		return;

	m_pThread = AfxBeginThread(
		ThreadTest03, NULL,
		THREAD_PRIORITY_NORMAL,
		0,
		CREATE_SUSPENDED);
	m_pThread->m_bAutoDelete = FALSE;
}


void CMy04threadCtrlView::OnThreadResume()
{
	m_pThread->ResumeThread();
}


void CMy04threadCtrlView::OnThreadSuspend()
{
	m_pThread->SuspendThread();
}

void CMy04threadCtrlView::OnThreadExit()
{
	g_bExit = TRUE;
	//Sleep(1500);
	if (::WaitForSingleObject(m_pThread->m_hThread,
		INFINITE) == WAIT_OBJECT_0)
	{
		delete m_pThread;
		m_pThread = NULL;
		AfxMessageBox(_T("작업자 스레드 종료"));
	}
}

void CMy04threadCtrlView::OnThreadTerminate()
{
	::TerminateThread(m_pThread->m_hThread, 0);
	delete m_pThread;
	m_pThread = NULL;
}



