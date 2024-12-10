
// 06_threadAndUiView.h: CMy06threadAndUiView 클래스의 인터페이스
//

#pragma once
#include "CInfoDlg.h"

#define UM_SETDATA (WM_USER + 100)

class CMy06threadAndUiView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy06threadAndUiView() noexcept;
	DECLARE_DYNCREATE(CMy06threadAndUiView)

// 특성입니다.
public:
	CMy06threadAndUiDoc* GetDocument() const;

	CInfoDlg m_wndInfo;

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
	virtual ~CMy06threadAndUiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDialogShow();
	afx_msg void OnDialogSetdata();
	afx_msg void OnDialogUsermessage();
	afx_msg LRESULT OnUmSetData(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // 06_threadAndUiView.cpp의 디버그 버전
inline CMy06threadAndUiDoc* CMy06threadAndUiView::GetDocument() const
   { return reinterpret_cast<CMy06threadAndUiDoc*>(m_pDocument); }
#endif

