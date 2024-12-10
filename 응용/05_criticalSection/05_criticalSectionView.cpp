
// 05_criticalSectionView.cpp: CMy05criticalSectionView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "05_criticalSection.h"
#endif

#include "05_criticalSectionDoc.h"
#include "05_criticalSectionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy05criticalSectionView

IMPLEMENT_DYNCREATE(CMy05criticalSectionView, CView)

BEGIN_MESSAGE_MAP(CMy05criticalSectionView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_CRITICAL_COUNTER, &CMy05criticalSectionView::OnCriticalCounter)
	ON_COMMAND(ID_CRITICAL_QUEUE, &CMy05criticalSectionView::OnCriticalQueue)
END_MESSAGE_MAP()

// CMy05criticalSectionView 생성/소멸

CMy05criticalSectionView::CMy05criticalSectionView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy05criticalSectionView::~CMy05criticalSectionView()
{
}

BOOL CMy05criticalSectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy05criticalSectionView 그리기

void CMy05criticalSectionView::OnDraw(CDC* /*pDC*/)
{
	CMy05criticalSectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy05criticalSectionView 인쇄

BOOL CMy05criticalSectionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy05criticalSectionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy05criticalSectionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy05criticalSectionView 진단

#ifdef _DEBUG
void CMy05criticalSectionView::AssertValid() const
{
	CView::AssertValid();
}

void CMy05criticalSectionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy05criticalSectionDoc* CMy05criticalSectionView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05criticalSectionDoc)));
	return (CMy05criticalSectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy05criticalSectionView 메시지 처리기

CCriticalSection g_cs;
int* g_pnCounter;

UINT ThreadCounter(LPVOID pParam)
{
	for (int i = 0; i < 100000; ++i)
	{
		g_cs.Lock();
		*g_pnCounter += 1;
		g_cs.Unlock();
	}
	return 0;
}

void CMy05criticalSectionView::OnCriticalCounter()
{
	g_pnCounter = new int;
	*g_pnCounter = 0;
	for (int i = 0; i < 3; ++i)
		AfxBeginThread(ThreadCounter, NULL);

	Sleep(1000);
	CString strTmp;
	strTmp.Format(_T("Counter: %d"), *g_pnCounter);
	AfxMessageBox(strTmp);
}


CList<int> g_list;

UINT ThreadAppendData(LPVOID pParam)
{
	for (int i = 0; i < 10000; ++i)
	{
		g_cs.Lock();
		g_list.AddTail(100);
		g_cs.Unlock();
		Sleep(1);
	}
	return 0;
}

UINT ThreadRemoveData(LPVOID pParam)
{
	while (1)
	{
		g_cs.Lock();
		int count = (int)g_list.GetCount();
		if(count > 0)
			g_list.RemoveHead();
		g_cs.Unlock();
		Sleep(1);
	}
	return 0;
}

void CMy05criticalSectionView::OnCriticalQueue()
{
	g_list.RemoveAll();
	AfxBeginThread(ThreadRemoveData, NULL);
	AfxBeginThread(ThreadAppendData, NULL);
}
