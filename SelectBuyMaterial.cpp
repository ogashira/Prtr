#include "SelectBuyMaterial.h"
#include <iostream>

SelectBuyMaterial::SelectBuyMaterial(CalcDateSingleton* myDate)
{
	this->myDate = myDate;
}

void SelectBuyMaterial::ExecuteStatement(
	std::vector<std::vector<std::string>>* psMaster
)
{
	//TCHAR     szBuf[1024];
	TCHAR     szCol1[25]{};
	TCHAR     szCol2[25]{};
	SQLLEN    nColLen1 = 0;
	SQLLEN    nColLen2 = 0;
	SQLRETURN nResult;

	std::string sttDay = myDate->calcStrSttDay();
	std::string endDay = myDate->calcStrEndDay();
	char c_sttday[10]; 
	strcpy_s(c_sttday, sttDay.size() + 1, sttDay.c_str());
	char c_endday[10]; 
	strcpy_s(c_endday, endDay.size() + 1, endDay.c_str());


	//sprintf_sを使って、文字と変数(fromDay, tillDay)を結合させたいので
	//char型にする
	char moji[254];
	sprintf_s(moji,
		"SELECT RssHinCD,SUM(RssUKSiSu) AS Syuukei"
		" FROM RSEISN"
		" WHERE RssUKDay >= %s AND RssUKDay <= %s" 
		" AND RssTehaiCD>='SI001' AND RssTehaiCD<='SI200'"
		" GROUP BY RssHinCD"
		" ORDER BY RssHinCD", c_sttday, c_endday);
	/*
	char h1[30] = "20230501";
	char h2[30] = "20240229";
	sprintf_s(moji,
		"SELECT TnkHinCD,TnkAitCD1,TnkDay,TnkTnk"
		" FROM MTANKA"
		" WHERE TnkDay>= %s AND TnkDay<= %s"
		" ORDER BY TnkHinCD,TnkAitCD1,TnkDay", h1, h2);
		*/


		//SQLExecDirectに渡すのに、wchar_t(TCHAR)型にしないといけないから
		//mbstowcsを使って変換する。visual studioのプロパティの設定で
		//SDLチェックを「いいえ」にしないと使えない(mbstowcs_s)が推奨されて
		//いるが、使い方がわからないから
	TCHAR wmoji[256]{};
	mbstowcs(wmoji, moji, (sizeof wmoji) / 2);


	ConnectSql* conSql = new ConnectSql();

	SQLHSTMT hstmt = conSql->connectSql("SelectBuyMaterial");
	//nResult = SQLExecDirect(hstmt, (SQLTCHAR*)TEXT(
	nResult = SQLExecDirect(hstmt, (SQLTCHAR*)wmoji, SQL_NTS);


	SQLBindCol(hstmt, 1, SQL_C_TCHAR, szCol1, sizeof(szCol1), &nColLen1);
	SQLBindCol(hstmt, 2, SQL_C_TCHAR, szCol2, sizeof(szCol2), &nColLen2);


	int cnt = 0;
	for (;;) {
		nResult = SQLFetch(hstmt);
		if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO) {
			std::vector<std::string> line;
			std::wstring col1(&szCol1[0]);                   //この２行で
			std::string strCol1(col1.begin(), col1.end());   //TCHAR型からstring型に変換
			std::wstring col2(&szCol2[0]);
			std::string strCol2(col2.begin(), col2.end());
			line.push_back(strCol1);
			line.push_back(strCol2);
			psMaster->push_back(line);
			cnt++;
		}
		else
			break;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	SQLDisconnect(hstmt);
	delete conSql;
	//MessageBox(NULL, szBuf, TEXT("OK"), MB_OK);
}
