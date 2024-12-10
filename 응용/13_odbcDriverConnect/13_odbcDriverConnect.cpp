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

    if (::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) !=
        SQL_SUCCESS)
        cout << "ERROR: SQLAllocHandle(SQL_HANDLE_ENV)" << endl;

    if (::SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
        cout << "ERROR: SQLSetEnvAttr()" << endl;

    if (::SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
        cout << "SQLAllocHandle(SQL_HANDLE_DBC)" << endl;

    SQLRETURN ret = SQLDriverConnect(hDbc, NULL,
        (SQLWCHAR*)L"DRIVER={MySQL ODBC 9.0 Unicode Driver};"
        L"SERVER=127.0.0.1;PORT=3306;"
        L"DATABASE=address;USER=root;PASSWORD=qaz123!@#;",
        SQL_NTS, (SQLWCHAR*)NULL, 0, NULL,
        SQL_DRIVER_NOPROMPT);

    if (ret == SQL_SUCCESS)
        cout << "DB connect: Success" << endl;
    else
    {
        cout << "DB connect: Failed" << endl;
        PrintMsg(hEnv, hDbc, hStmt);
    }


    ::SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


    SQLLEN lName = SQL_NTS, lPhone = SQL_NTS, lAge = SQL_NTS;
    TCHAR name[256] = { 0 }, phone[256] = { 0 };
    int age = 0;

    ret = ::SQLBindCol(hStmt, 1, SQL_C_WCHAR, name, sizeof(name), &lName);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        cout << "Bind Success!" << endl;
    ret = ::SQLBindCol(hStmt, 2, SQL_C_WCHAR, phone, sizeof(phone), &lPhone);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        cout << "Bind Success!" << endl;
    ret = ::SQLBindCol(hStmt, 4, SQL_C_ULONG, &age, 0, &lAge);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        cout << "Bind Success!" << endl;

    ret = ::SQLExecDirect(hStmt,
        (SQLTCHAR*)L"SELECT * FROM address.userinfo limit 10;",
        SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        PrintMsg(hEnv, hDbc, hStmt);

    for (int i = 0; ; i++) {
        ret = ::SQLFetch(hStmt);
        if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
            PrintMsg(hEnv, hDbc, hStmt);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        {
            wcout << name << ", " << phone << ", " << age << endl;
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
