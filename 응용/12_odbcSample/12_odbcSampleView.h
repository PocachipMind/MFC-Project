
// 12_odbcSampleView.h: CMy12odbcSampleView 클래스의 인터페이스
//

#pragma once


class CMy12odbcSampleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy12odbcSampleView() noexcept;
	DECLARE_DYNCREATE(CMy12odbcSampleView)

// 특성입니다.
public:
	CMy12odbcSampleDoc* GetDocument() const;

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
	virtual ~CMy12odbcSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDatabaseOpen();
	afx_msg void OnDatabaseInsert();
	afx_msg void OnDatabaseUpdate();
	afx_msg void OnDatabaseDelete();
	afx_msg void OnDatabaseClose();
	afx_msg void OnDatabaseSelect();
};

#ifndef _DEBUG  // 12_odbcSampleView.cpp의 디버그 버전
inline CMy12odbcSampleDoc* CMy12odbcSampleView::GetDocument() const
   { return reinterpret_cast<CMy12odbcSampleDoc*>(m_pDocument); }
#endif

