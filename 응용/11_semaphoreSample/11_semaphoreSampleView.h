
// 11_semaphoreSampleView.h: CMy11semaphoreSampleView 클래스의 인터페이스
//

#pragma once


class CMy11semaphoreSampleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy11semaphoreSampleView() noexcept;
	DECLARE_DYNCREATE(CMy11semaphoreSampleView)

// 특성입니다.
public:
	CMy11semaphoreSampleDoc* GetDocument() const;

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
	virtual ~CMy11semaphoreSampleView();
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
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // 11_semaphoreSampleView.cpp의 디버그 버전
inline CMy11semaphoreSampleDoc* CMy11semaphoreSampleView::GetDocument() const
   { return reinterpret_cast<CMy11semaphoreSampleDoc*>(m_pDocument); }
#endif

