
// 11_semaphoreSampleView.cpp: CMy11semaphoreSampleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "11_semaphoreSample.h"
#endif

#include "11_semaphoreSampleDoc.h"
#include "11_semaphoreSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy11semaphoreSampleView

IMPLEMENT_DYNCREATE(CMy11semaphoreSampleView, CView)

BEGIN_MESSAGE_MAP(CMy11semaphoreSampleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMy11semaphoreSampleView 생성/소멸

CMy11semaphoreSampleView::CMy11semaphoreSampleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy11semaphoreSampleView::~CMy11semaphoreSampleView()
{
}

BOOL CMy11semaphoreSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy11semaphoreSampleView 그리기

void CMy11semaphoreSampleView::OnDraw(CDC* /*pDC*/)
{
	CMy11semaphoreSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy11semaphoreSampleView 인쇄

BOOL CMy11semaphoreSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy11semaphoreSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy11semaphoreSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy11semaphoreSampleView 진단

#ifdef _DEBUG
void CMy11semaphoreSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMy11semaphoreSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy11semaphoreSampleDoc* CMy11semaphoreSampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11semaphoreSampleDoc)));
	return (CMy11semaphoreSampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy11semaphoreSampleView 메시지 처리기

CSemaphore g_sp(3, 3);
CString g_aThreadInfo[10];
BOOL g_bExitFlag = FALSE;

UINT ThreadSema(LPVOID pParam)
{
	int idx = (int)(long long)pParam;
	while (!g_bExitFlag)
	{
		g_aThreadInfo[idx].Format(_T("Thread%02d is waiting..."), idx);
		
		g_sp.Lock();
		g_aThreadInfo[idx].Format(_T("##Thread%02d is running!"), idx);
		Sleep(100);
		g_sp.Unlock();
	}
	g_aThreadInfo[idx].Format(_T("Thread%02d is finished."), idx);
	return 0;
}

int CMy11semaphoreSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	for (long long i = 0; i < 10; ++i)
		AfxBeginThread(ThreadSema, (LPVOID)i);

	SetTimer(5, 1000, NULL);
	return 0;
}


void CMy11semaphoreSampleView::OnClose()
{
	CView::OnClose();
}


void CMy11semaphoreSampleView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 5)
	{
		RedrawWindow();
		CClientDC dc(this);

		for (int i = 0; i < 10; ++i)
		{
			if (g_aThreadInfo[i].GetAt(0) == _T('#'))
				dc.SetTextColor(RGB(192, 0, 0));
			else
				dc.SetTextColor(RGB(192, 192, 192));

			dc.TextOut(10, i * 20 + 10, g_aThreadInfo[i]);
		}
	}

	CView::OnTimer(nIDEvent);
}


void CMy11semaphoreSampleView::OnDestroy()
{
	KillTimer(5);
	g_bExitFlag = TRUE;

	Sleep(2000);

	CView::OnDestroy();
}
