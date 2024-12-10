
// 02_workerThreadView.cpp: CMy02workerThreadView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "02_workerThread.h"
#endif

#include "02_workerThreadDoc.h"
#include "02_workerThreadView.h"

#include "CParamObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy02workerThreadView

IMPLEMENT_DYNCREATE(CMy02workerThreadView, CView)

BEGIN_MESSAGE_MAP(CMy02workerThreadView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_BEGIN, &CMy02workerThreadView::OnThreadBegin)
END_MESSAGE_MAP()

// CMy02workerThreadView 생성/소멸

CMy02workerThreadView::CMy02workerThreadView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy02workerThreadView::~CMy02workerThreadView()
{
}

BOOL CMy02workerThreadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy02workerThreadView 그리기

void CMy02workerThreadView::OnDraw(CDC* /*pDC*/)
{
	CMy02workerThreadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy02workerThreadView 인쇄

BOOL CMy02workerThreadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy02workerThreadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy02workerThreadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy02workerThreadView 진단

#ifdef _DEBUG
void CMy02workerThreadView::AssertValid() const
{
	CView::AssertValid();
}

void CMy02workerThreadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy02workerThreadDoc* CMy02workerThreadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy02workerThreadDoc)));
	return (CMy02workerThreadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy02workerThreadView 메시지 처리기


UINT CMy02workerThreadView::ThreadTest(LPVOID pParam)
{
	CParamObj* pParamObj = (CParamObj*)pParam;
	OutputDebugString(_T("ThreadTest() - Begin\n"));
	Sleep(5000);
	delete pParamObj;
	OutputDebugString(_T("ThreadTest() - End\n"));
	return 0;
}

void CMy02workerThreadView::OnThreadBegin()
{
	CParamObj* pParam = new CParamObj;
	AfxBeginThread(CMy02workerThreadView::ThreadTest, pParam);
	OutputDebugString(_T("OnThreadBegin() - return\n"));
}