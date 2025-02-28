#include "ConnectSql.h"
#include <iostream>
#include <stdio.h>



SQLHSTMT ConnectSql::connectSql(std::string dataName)
{
	SQLHENV     henv;
	SQLHDBC     hdbc;
	SQLHSTMT    hstmt;
	SQLRETURN   nResult;
	SQLSMALLINT nSize;
	TCHAR       szState[6]{};
	TCHAR       szErrorMsg[1024]{};
	SQLINTEGER  nErrorCode;
	SQLTCHAR    szConnStrOut[1024]{};
	SQLSMALLINT cchConnStrOut = 0;

	nResult = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO)
		return 0;

	nResult = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return 0;
	}

	nResult = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return 0;
	}
	

	//TODOÇ±Ç±ÇèëÇ´ä∑Ç¶ÇÈ
	SQLTCHAR pass[100] = L"hoge";


	nResult = SQLDriverConnect(hdbc,NULL, (SQLTCHAR*)pass,
		SQL_NTS,(SQLTCHAR*)szConnStrOut,sizeof(szConnStrOut)/sizeof(SQLTCHAR), &nSize, SQL_DRIVER_NOPROMPT);

	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, 1, (SQLTCHAR*)szState, &nErrorCode, (SQLTCHAR*)szErrorMsg, sizeof(szErrorMsg) / sizeof(TCHAR), &nSize);
		MessageBox(NULL, szErrorMsg, NULL, MB_ICONWARNING);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		std::cout << dataName << "ê⁄ë±é∏îs" << std::endl;
		return 0;
	}
	else {
		std::cout << dataName << "ê⁄ë±ê¨å˜" << std::endl;
	}

	nResult = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (nResult != SQL_SUCCESS && nResult != SQL_SUCCESS_WITH_INFO) {
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return 0;
	}


	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return hstmt;

}
