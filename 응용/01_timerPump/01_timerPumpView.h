
// 01_timerPumpView.h: CMy01timerPumpView 클래스의 인터페이스
//

#pragma once


class CMy01timerPumpView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy01timerPumpView() noexcept;
	DECLARE_DYNCREATE(CMy01timerPumpView)

// 특성입니다.
public:
	CMy01timerPumpDoc* GetDocument() const;

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
	virtual ~CMy01timerPumpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestCounter();
	BOOL PeekAndPump();
};

#ifndef _DEBUG  // 01_timerPumpView.cpp의 디버그 버전
inline CMy01timerPumpDoc* CMy01timerPumpView::GetDocument() const
   { return reinterpret_cast<CMy01timerPumpDoc*>(m_pDocument); }
#endif

