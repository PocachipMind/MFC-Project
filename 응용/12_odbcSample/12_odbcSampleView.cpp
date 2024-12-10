
// 12_odbcSampleView.cpp: CMy12odbcSampleView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "12_odbcSample.h"
#endif

#include "12_odbcSampleDoc.h"
#include "12_odbcSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy12odbcSampleView

IMPLEMENT_DYNCREATE(CMy12odbcSampleView, CView)

BEGIN_MESSAGE_MAP(CMy12odbcSampleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DATABASE_OPEN, &CMy12odbcSampleView::OnDatabaseOpen)
	ON_COMMAND(ID_DATABASE_INSERT, &CMy12odbcSampleView::OnDatabaseInsert)
	ON_COMMAND(ID_DATABASE_UPDATE, &CMy12odbcSampleView::OnDatabaseUpdate)
	ON_COMMAND(ID_DATABASE_DELETE, &CMy12odbcSampleView::OnDatabaseDelete)
	ON_COMMAND(ID_DATABASE_CLOSE, &CMy12odbcSampleView::OnDatabaseClose)
	ON_COMMAND(ID_DATABASE_SELECT, &CMy12odbcSampleView::OnDatabaseSelect)
END_MESSAGE_MAP()

// CMy12odbcSampleView 생성/소멸

CMy12odbcSampleView::CMy12odbcSampleView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy12odbcSampleView::~CMy12odbcSampleView()
{
}

BOOL CMy12odbcSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy12odbcSampleView 그리기

void CMy12odbcSampleView::OnDraw(CDC* /*pDC*/)
{
	CMy12odbcSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy12odbcSampleView 인쇄

BOOL CMy12odbcSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy12odbcSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy12odbcSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy12odbcSampleView 진단

#ifdef _DEBUG
void CMy12odbcSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMy12odbcSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12odbcSampleDoc* CMy12odbcSampleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12odbcSampleDoc)));
	return (CMy12odbcSampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy12odbcSampleView 메시지 처리기


void CMy12odbcSampleView::OnDatabaseOpen()
{
	CDatabase &db = GetDocument()->m_dbAddr;
	db.OpenEx(_T("DSN=AddressBook;ODBC;"),
		CDatabase::noOdbcDialog);
}

void CMy12odbcSampleView::OnDatabaseClose()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.Close();
}

void CMy12odbcSampleView::OnDatabaseSelect()
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


void CMy12odbcSampleView::OnDatabaseInsert()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.ExecuteSQL(
		_T("insert into address.userinfo ")
		_T("values('김길동', '01-5555-5555', '대전', 20);")
	);
}

void CMy12odbcSampleView::OnDatabaseUpdate()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.ExecuteSQL(
		_T("update address.userinfo set ")
		_T("phone = '02-2222-2222', age = 18 ")
		_T("where name = '홍길동';")
	);
}

void CMy12odbcSampleView::OnDatabaseDelete()
{
	CDatabase& db = GetDocument()->m_dbAddr;
	db.ExecuteSQL(
		_T("delete from address.userinfo ")
		_T("where name = '김길동';")
	);
}

