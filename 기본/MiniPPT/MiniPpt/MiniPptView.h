
// MiniPptView.h: CMiniPptView 클래스의 인터페이스
//

#pragma once

class CMyShape;


class CMiniPptView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMiniPptView() noexcept;
	DECLARE_DYNCREATE(CMiniPptView)

// 특성입니다.
public:
	CMiniPptDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMiniPptView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bDrag = FALSE;

	BOOL m_bDraw = FALSE;
	CPoint m_ptBegin;
	CPoint m_ptEnd;


	CPtrList m_listShape;

	COLORREF m_cBrush = RGB(255, 0, 0);


// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	CMyShape* PtInShapes(CPoint point);
	void ReleaseList();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShapeBrushred();
	afx_msg void OnShapeBrushgreen();
	afx_msg void OnShapeBrushblue();
	afx_msg void OnUpdateShapeBrushred(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShapeBrushgreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShapeBrushblue(CCmdUI* pCmdUI);
	afx_msg void OnMyfileLoad();
	afx_msg void OnMyfileSave();
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // MiniPptView.cpp의 디버그 버전
inline CMiniPptDoc* CMiniPptView::GetDocument() const
   { return reinterpret_cast<CMiniPptDoc*>(m_pDocument); }
#endif

