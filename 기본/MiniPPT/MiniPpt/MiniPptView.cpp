
// MiniPptView.cpp: CMiniPptView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MiniPpt.h"
#endif

#include "MiniPptDoc.h"
#include "MiniPptView.h"

#include "CMyShape.h"
#include "BufferDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniPptView

IMPLEMENT_DYNCREATE(CMiniPptView, CView)

BEGIN_MESSAGE_MAP(CMiniPptView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_SHAPE_BRUSHRED, &CMiniPptView::OnShapeBrushred)
	ON_COMMAND(ID_SHAPE_BRUSHGREEN, &CMiniPptView::OnShapeBrushgreen)
	ON_COMMAND(ID_SHAPE_BRUSHBLUE, &CMiniPptView::OnShapeBrushblue)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_BRUSHRED, &CMiniPptView::OnUpdateShapeBrushred)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_BRUSHGREEN, &CMiniPptView::OnUpdateShapeBrushgreen)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_BRUSHBLUE, &CMiniPptView::OnUpdateShapeBrushblue)
	ON_COMMAND(ID_MYFILE_LOAD, &CMiniPptView::OnMyfileLoad)
	ON_COMMAND(ID_MYFILE_SAVE, &CMiniPptView::OnMyfileSave)
END_MESSAGE_MAP()

// CMiniPptView 생성/소멸

CMiniPptView::CMiniPptView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMiniPptView::~CMiniPptView()
{
	ReleaseList();
}

BOOL CMiniPptView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMiniPptView 그리기

void CMiniPptView::OnDraw(CDC* /*pDC*/)
{
	CMiniPptDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMiniPptView 인쇄

BOOL CMiniPptView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMiniPptView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMiniPptView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMiniPptView 진단

#ifdef _DEBUG
void CMiniPptView::AssertValid() const
{
	CView::AssertValid();
}

void CMiniPptView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMiniPptDoc* CMiniPptView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniPptDoc)));
	return (CMiniPptDoc*)m_pDocument;
}
#endif //_DEBUG


// CMiniPptView 메시지 처리기


void CMiniPptView::OnPaint()
{
	//CPaintDC dc(this);
	CBufferDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect, RGB(255, 255, 255));

	CMyShape* pShape = NULL;

	POSITION pos = m_listShape.GetHeadPosition();
	while (pos != NULL)
	{
		pShape = (CMyShape*)m_listShape.GetAt(pos);

		CPen pen(PS_SOLID, pShape->m_nPenWidth, pShape->m_cPen);
		CPen *pOldPen = dc.SelectObject(&pen);
		CBrush brush(pShape->m_cBrush);
		CBrush* pOldBrush = dc.SelectObject(&brush);

		dc.Rectangle(
			pShape->m_point.x, pShape->m_point.y,
			pShape->m_point.x + pShape->m_size.cx,
			pShape->m_point.y + pShape->m_size.cy
		);

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		m_listShape.GetNext(pos);
	}
}


void CMiniPptView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMyShape* pShape = PtInShapes(point);
	if (pShape != NULL)
	{
		POSITION pos = m_listShape.Find(pShape);
		m_listShape.RemoveAt(pos);
		m_listShape.AddTail(pShape);

		RedrawWindow();
	}
	else
	{
		m_bDraw = TRUE;
	}
	
	
	m_ptBegin = point;

	CView::OnLButtonDown(nFlags, point);
}


void CMiniPptView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDraw)
	{
		m_ptEnd = point;
		m_bDraw = FALSE;

		//새 도형 생성
		CMyShape *pNewShape = new CMyShape;
		//pNewShape->m_point = m_ptBegin;
		//pNewShape->m_size = m_ptEnd - m_ptBegin;

		pNewShape->m_point.x =
			(m_ptBegin.x < m_ptEnd.x) ? m_ptBegin.x: m_ptEnd.x;
		pNewShape->m_point.y =
			(m_ptBegin.y < m_ptEnd.y) ? m_ptBegin.y : m_ptEnd.y;

		pNewShape->m_size = m_ptEnd - m_ptBegin;
		pNewShape->m_size.cx = abs(pNewShape->m_size.cx);
		pNewShape->m_size.cy = abs(pNewShape->m_size.cy);

		pNewShape->m_cBrush = this->m_cBrush;

		m_listShape.AddTail(pNewShape);
		RedrawWindow();
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMiniPptView::OnMove(int x, int y)
{
	CView::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


CMyShape* CMiniPptView::PtInShapes(CPoint point)
{
	CMyShape* pShape = NULL;
	POSITION pos = m_listShape.GetTailPosition();
	while (pos != NULL)
	{
		pShape = (CMyShape*)m_listShape.GetAt(pos);
		if (pShape->PtInShape(point))
			return pShape;

		m_listShape.GetPrev(pos);
	}
	return nullptr;
}


void CMiniPptView::ReleaseList()
{
	CMyShape* pShape = NULL;

	POSITION pos = m_listShape.GetHeadPosition();
	while (pos != NULL)
	{
		pShape = (CMyShape*)m_listShape.GetAt(pos);
		delete pShape;
		m_listShape.GetNext(pos);
	}

	m_listShape.RemoveAll();
}


void CMiniPptView::OnDestroy()
{
	CView::OnDestroy();
	ReleaseList();
}


BOOL CMiniPptView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CMiniPptView::OnShapeBrushred()
{
	m_cBrush = RGB(255, 0, 0);
}


void CMiniPptView::OnShapeBrushgreen()
{
	m_cBrush = RGB(0, 255, 0);
}


void CMiniPptView::OnShapeBrushblue()
{
	m_cBrush = RGB(0, 0, 255);
}


void CMiniPptView::OnUpdateShapeBrushred(CCmdUI* pCmdUI)
{
	if(m_cBrush == RGB(255, 0, 0))
		pCmdUI->SetRadio(1);
	else
		pCmdUI->SetRadio(0);
}


void CMiniPptView::OnUpdateShapeBrushgreen(CCmdUI* pCmdUI)
{
	if (m_cBrush == RGB(0, 255, 0))
		pCmdUI->SetRadio(1);
	else
		pCmdUI->SetRadio(0);
}


void CMiniPptView::OnUpdateShapeBrushblue(CCmdUI* pCmdUI)
{
	if (m_cBrush == RGB(0, 0, 255))
		pCmdUI->SetRadio(1);
	else
		pCmdUI->SetRadio(0);
}


void CMiniPptView::OnMyfileLoad()
{
	ReleaseList();

	FILE* fp = NULL;
	fopen_s(&fp, "test.pptmini", "rb");

	CMyShape::MYSHAPE shape = { 0 };
	while (fread(&shape, sizeof(shape), 1, fp))
	{
		CMyShape* pShape = new CMyShape;
		pShape->m_point = CPoint(shape.x, shape.y);
		pShape->m_size = CSize(shape.cx, shape.cy);
		pShape->m_cBrush = shape.cbrush;

		m_listShape.AddTail(pShape);
	}

	fclose(fp);
	RedrawWindow();
}


void CMiniPptView::OnMyfileSave()
{
	FILE* fp = NULL;
	fopen_s(&fp, "test.pptmini", "wb");

	CMyShape* pShape = NULL;
	POSITION pos = m_listShape.GetHeadPosition();
	while (pos != NULL)
	{
		pShape = (CMyShape*)m_listShape.GetAt(pos);
		CMyShape::MYSHAPE shape = pShape->GetData();

		fwrite(&shape, sizeof(shape), 1, fp);

		m_listShape.GetNext(pos);
	}

	fclose(fp);
}


void CMiniPptView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//AfxMessageBox(_T("OnInitialUpdate()"));
}


void CMiniPptView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	//AfxMessageBox(_T("OnUpdate()"));
}
