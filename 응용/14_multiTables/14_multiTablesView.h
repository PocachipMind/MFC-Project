
// 14_multiTablesView.h: CMy14multiTablesView 클래스의 인터페이스
//

#pragma once


class CMy14multiTablesView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy14multiTablesView() noexcept;
	DECLARE_DYNCREATE(CMy14multiTablesView)

// 특성입니다.
public:
	CMy14multiTablesDoc* GetDocument() const;

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
	virtual ~CMy14multiTablesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDatabaseTables();
};

#ifndef _DEBUG  // 14_multiTablesView.cpp의 디버그 버전
inline CMy14multiTablesDoc* CMy14multiTablesView::GetDocument() const
   { return reinterpret_cast<CMy14multiTablesDoc*>(m_pDocument); }
#endif

