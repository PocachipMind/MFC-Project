
// 16_transSampleView.cpp: CMy16transSampleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "16_transSample.h"
#endif

#include "16_transSampleDoc.h"
#include "16_transSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy16transSampleView

IMPLEMENT_DYNCREATE(CMy16transSampleView, CView)

BEGIN_MESSAGE_MAP(CMy16transSampleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DATABASE_OEPN, &CMy16transSampleView::OnDatabaseOepn)
	ON_COMMAND(ID_DATABASE_CLOSE, &CMy16transSampleView::OnDatabaseClose)
	ON_COMMAND(ID_DATABASE_SELECT, &CMy16transSampleView::OnDatabaseSelect)
	ON_COMMAND(ID_TRANSACTION_BEGIN, &CMy16transSampleView::OnTransactionBegin)
	ON_COMMAND(ID_TRANSACTION_END, &CMy16transSampleView::OnTransactionEnd)
	ON_COMMAND(ID_TRANSACTION_ROLLBACK, &CMy16transSampleView::OnTransactionRollback)
	ON_COMMAND(ID_DATABASE_DELETE, &CMy16transSampleView::OnDatabaseDelete)
END_MESSAGE_MAP()

// CMy16transSampleView 생성/소멸

CMy16transSampleView::CMy16transSampleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy16transSampleView::~CMy16transSampleView()
{
}

BOOL CMy16transSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy16transSampleView 그리기

void CMy16transSampleView::OnDraw(CDC* /*pDC*/)
{
	CMy16transSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy16transSampleView 인쇄

BOOL CMy16transSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy16transSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy16transSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy16transSampleView 진단

#ifdef _DEBUG
void CMy16transSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMy16transSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy16transSampleDoc* CMy16transSampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy16transSampleDoc)));
	return (CMy16transSampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy16transSampleView 메시지 처리기


void CMy16transSampleView::OnDatabaseOepn()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.OpenEx(_T("DSN=AddressBook;ODBC;"),
		CDatabase::noOdbcDialog);
}


void CMy16transSampleView::OnDatabaseClose()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.Close();
}


void CMy16transSampleView::OnDatabaseSelect()
{
	CDatabase& db = GetDocument()->m_dbAddr;

	CRecordset recset(&db);
	recset.Open(CRecordset::snapshot,
		_T("SELECT * FROM address.userinfo limit 10"));

	CString strName, strPhone, strAge, strTmp;
	CClientDC dc(this);
	RedrawWindow();
	for (int i = 0; !recset.IsEOF(); i++)
	{
		recset.GetFieldValue(_T("name"), strName);
		recset.GetFieldValue(_T("phone"), strPhone);
		recset.GetFieldValue(_T("age"), strAge);

		strTmp.Format(_T("%s, %s, %s"),
			strName, strPhone, strAge);

		dc.TextOut(10, i * 20 + 10, strTmp);
		recset.MoveNext();
	}
}


void CMy16transSampleView::OnTransactionBegin()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	if (!db.CanTransact())
	{
		AfxMessageBox(_T("DB가 트랜젝션을 지원하지 않습니다."));
		return;
	}

	db.BeginTrans();

	db.ExecuteSQL(
		_T("insert into address.userinfo ")
		_T("values('김철수', '01-3333-3333', '부산', 12);")
	);
}


void CMy16transSampleView::OnTransactionEnd()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.CommitTrans();
}


void CMy16transSampleView::OnTransactionRollback()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.Rollback();
}


void CMy16transSampleView::OnDatabaseDelete()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.ExecuteSQL(
		_T("delete from address.userinfo ")
		_T("where name = '김철수';")
	);
}
