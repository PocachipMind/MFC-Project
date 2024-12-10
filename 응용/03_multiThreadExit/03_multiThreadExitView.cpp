
// 03_multiThreadExitView.cpp: CMy03multiThreadExitView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "03_multiThreadExit.h"
#endif

#include "03_multiThreadExitDoc.h"
#include "03_multiThreadExitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy03multiThreadExitView

IMPLEMENT_DYNCREATE(CMy03multiThreadExitView, CView)

BEGIN_MESSAGE_MAP(CMy03multiThreadExitView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_FLAG, &CMy03multiThreadExitView::OnThreadFlag)
	ON_COMMAND(ID_THREAD_EXITALL, &CMy03multiThreadExitView::OnThreadExitall)
	ON_COMMAND(ID_THREAD_WAIT, &CMy03multiThreadExitView::OnThreadWait)
END_MESSAGE_MAP()

// CMy03multiThreadExitView 생성/소멸

CMy03multiThreadExitView::CMy03multiThreadExitView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy03multiThreadExitView::~CMy03multiThreadExitView()
{
}

BOOL CMy03multiThreadExitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy03multiThreadExitView 그리기

void CMy03multiThreadExitView::OnDraw(CDC* /*pDC*/)
{
	CMy03multiThreadExitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy03multiThreadExitView 인쇄

BOOL CMy03multiThreadExitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy03multiThreadExitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy03multiThreadExitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy03multiThreadExitView 진단

#ifdef _DEBUG
void CMy03multiThreadExitView::AssertValid() const
{
	CView::AssertValid();
}

void CMy03multiThreadExitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy03multiThreadExitDoc* CMy03multiThreadExitView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy03multiThreadExitDoc)));
	return (CMy03multiThreadExitDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy03multiThreadExitView 메시지 처리기

BOOL g_bQuit = FALSE;

UINT ThreadTest01(LPVOID pParam)
{
	OutputDebugString(_T("ThreadTest01() - Begin\n"));
	while (!g_bQuit)
	{
		Sleep(100);
	}
	OutputDebugString(_T("ThreadTest01() - End\n"));
	return 0;
}

void CMy03multiThreadExitView::OnThreadFlag()
{
	g_bQuit = FALSE;
	for(int i = 0; i < 5;  ++i)
		AfxBeginThread(ThreadTest01, NULL);
}


void CMy03multiThreadExitView::OnThreadExitall()
{
	g_bQuit = TRUE;
	Sleep(500);
}


UINT ThreadTest02(LPVOID pParam)
{
	OutputDebugString(_T("ThreadTest02() - Begin\n"));
	Sleep(2000);
	OutputDebugString(_T("ThreadTest02() - End\n"));
	return 0;
}

UINT ThreadWaitForThread(LPVOID pParam)
{
	HANDLE hThread = AfxBeginThread(ThreadTest02, NULL)->m_hThread;
	if (::WaitForSingleObject(hThread, INFINITE) == WAIT_OBJECT_0)
		AfxMessageBox(_T("ThreadTest02() complete!"));
	return 0;
}

void CMy03multiThreadExitView::OnThreadWait()
{
	AfxBeginThread(ThreadWaitForThread, NULL);
}
