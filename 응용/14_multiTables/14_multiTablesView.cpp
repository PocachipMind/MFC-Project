
// 14_multiTablesView.cpp: CMy14multiTablesView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "14_multiTables.h"
#endif

#include "14_multiTablesDoc.h"
#include "14_multiTablesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy14multiTablesView

IMPLEMENT_DYNCREATE(CMy14multiTablesView, CView)

BEGIN_MESSAGE_MAP(CMy14multiTablesView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DATABASE_TABLES, &CMy14multiTablesView::OnDatabaseTables)
END_MESSAGE_MAP()

// CMy14multiTablesView 생성/소멸

CMy14multiTablesView::CMy14multiTablesView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy14multiTablesView::~CMy14multiTablesView()
{
}

BOOL CMy14multiTablesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy14multiTablesView 그리기

void CMy14multiTablesView::OnDraw(CDC* /*pDC*/)
{
	CMy14multiTablesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy14multiTablesView 인쇄

BOOL CMy14multiTablesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy14multiTablesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy14multiTablesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy14multiTablesView 진단

#ifdef _DEBUG
void CMy14multiTablesView::AssertValid() const
{
	CView::AssertValid();
}

void CMy14multiTablesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy14multiTablesDoc* CMy14multiTablesView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy14multiTablesDoc)));
	return (CMy14multiTablesDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy14multiTablesView 메시지 처리기


void CMy14multiTablesView::OnDatabaseTables()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.OpenEx(_T("DSN=AddressBook;ODBC;"),
		CDatabase::noOdbcDialog);

	CRecordset recsetUser(&db);

	recsetUser.Open(CRecordset::snapshot,
		_T("SELECT * FROM address.userinfo limit 10"));

	CString strName, strPhone, strAge, strTmp;
	CClientDC dc(this);
	for (int i = 0; !recsetUser.IsEOF(); i++)
	{
		recsetUser.GetFieldValue(_T("name"), strName);
		recsetUser.GetFieldValue(_T("phone"), strPhone);
		recsetUser.GetFieldValue(_T("age"), strAge);

		strTmp.Format(_T("%s, %s, %s"),
			strName, strPhone, strAge);

		dc.TextOut(10, i * 20 + 10, strTmp);
		recsetUser.MoveNext();
	}

	CRecordset recsetBook(&db);
	recsetBook.Open(CRecordset::snapshot,
		_T("SELECT * FROM address.book limit 10"));

	CString strTitle, strAuthor;
	for (int i = 0; !recsetBook.IsEOF(); i++)
	{
		recsetBook.GetFieldValue(_T("title"), strTitle);
		recsetBook.GetFieldValue(_T("author"), strAuthor);
		strTmp.Format(_T("%s, %s"),
			strTitle, strAuthor);

		dc.TextOut(200, i * 20 + 10, strTmp);
		recsetBook.MoveNext();
	}

	db.Close();
}
