
// 04_threadCtrlView.h: CMy04threadCtrlView 클래스의 인터페이스
//

#pragma once


class CMy04threadCtrlView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy04threadCtrlView() noexcept;
	DECLARE_DYNCREATE(CMy04threadCtrlView)

// 특성입니다.
public:
	CMy04threadCtrlDoc* GetDocument() const;

	CWinThread* m_pThread = NULL;

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
	virtual ~CMy04threadCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnThreadSuspended();
	afx_msg void OnThreadResume();
	afx_msg void OnThreadSuspend();
	afx_msg void OnThreadTerminate();
	afx_msg void OnThreadExit();
};

#ifndef _DEBUG  // 04_threadCtrlView.cpp의 디버그 버전
inline CMy04threadCtrlDoc* CMy04threadCtrlView::GetDocument() const
   { return reinterpret_cast<CMy04threadCtrlDoc*>(m_pDocument); }
#endif

