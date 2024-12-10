
// 02_workerThreadView.h: CMy02workerThreadView 클래스의 인터페이스
//

#pragma once


class CMy02workerThreadView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy02workerThreadView() noexcept;
	DECLARE_DYNCREATE(CMy02workerThreadView)

// 특성입니다.
public:
	CMy02workerThreadDoc* GetDocument() const;

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
	virtual ~CMy02workerThreadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnThreadBegin();
	static UINT ThreadTest(LPVOID pParam);
};

#ifndef _DEBUG  // 02_workerThreadView.cpp의 디버그 버전
inline CMy02workerThreadDoc* CMy02workerThreadView::GetDocument() const
   { return reinterpret_cast<CMy02workerThreadDoc*>(m_pDocument); }
#endif

