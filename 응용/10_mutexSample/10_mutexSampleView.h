﻿
// 10_mutexSampleView.h: CMy10mutexSampleView 클래스의 인터페이스
//

#pragma once


class CMy10mutexSampleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy10mutexSampleView() noexcept;
	DECLARE_DYNCREATE(CMy10mutexSampleView)

// 특성입니다.
public:
	CMy10mutexSampleDoc* GetDocument() const;

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
	virtual ~CMy10mutexSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMutexLock();
	afx_msg void OnMutexUnlock();
};

#ifndef _DEBUG  // 10_mutexSampleView.cpp의 디버그 버전
inline CMy10mutexSampleDoc* CMy10mutexSampleView::GetDocument() const
   { return reinterpret_cast<CMy10mutexSampleDoc*>(m_pDocument); }
#endif

