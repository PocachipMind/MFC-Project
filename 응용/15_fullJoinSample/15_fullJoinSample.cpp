#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>


using namespace std;

void PrintMsg(SQLHENV hEnv, SQLHDBC hDbc, SQLHSTMT hStmt)
{
    SQLTCHAR szState[SQL_SQLSTATE_SIZE + 1] = { 0 };
    SQLTCHAR szError[SQL_MAX_MESSAGE_LENGTH + 1] = { 0 };
    SQLINTEGER nCode = 0;
    SQLSMALLINT length = 0;

    ::SQLError(hEnv, hDbc, hStmt,
        szState, &nCode, szError, sizeof(szError), &length);
    wcout << szError << endl;
}

int main()
{
    setlocale(LC_ALL, "");

    SQLHENV hEnv = 0;
    SQLHDBC hDbc = 0;
    SQLHSTMT hStmt = 0;

    ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ::SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER);
    ::SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    TCHAR szInConnect[256] = { L"DSN=AddressBook;ODBC;" };
    TCHAR szOutConnect[256] = { 0 };
    SQLSMALLINT cbLen = 0;

    SQLRETURN ret = SQLConnect(hDbc,
        (SQLWCHAR*)L"AddressBook",
        SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        cout << "Success!" << endl;

    ::SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


    SQLLEN lIsbn = SQL_NTS;
    SQLLEN lTitle = SQL_NTS;
    SQLLEN lAuther = SQL_NTS;
    SQLLEN lPhone = SQL_NTS;

    TCHAR isbn[128] = { 0 };
    TCHAR title[256] = { 0 };
    TCHAR author[256] = { 0 };
    TCHAR phone[256] = { 0 };

    ret = ::SQLBindCol(hStmt, 1, SQL_C_WCHAR, isbn, sizeof(isbn), &lIsbn);
    ret = ::SQLBindCol(hStmt, 2, SQL_C_WCHAR, title, sizeof(title), &lTitle);
    ret = ::SQLBindCol(hStmt, 3, SQL_C_WCHAR, author, sizeof(author), &lAuther);
    ret = ::SQLBindCol(hStmt, 4, SQL_C_WCHAR, phone, sizeof(phone), &lPhone);

    ret = ::SQLExecDirect(hStmt,
        (SQLTCHAR*)L"SELECT "
        L"book.isbn, book.title, book.author, userinfo.phone "
        L"FROM book LEFT JOIN userinfo "
        L"ON book.author = userinfo.name;",
        SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        PrintMsg(hEnv, hDbc, hStmt);

    for (int i = 0; ; i++) {
        ret = SQLFetch(hStmt);
        if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
            PrintMsg(hEnv, hDbc, hStmt);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        {
            wcout << isbn << ", " << title << ", " 
                << author << ", " << phone << endl;
        }
        else
            break;
    }

    //Free & Disconnect
    ::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    ::SQLDisconnect(hDbc);
    ::SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    ::SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
