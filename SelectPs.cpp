#include "SelectPs.h"

void SelectPs::ExecuteStatement(
	                        std::vector<std::vector<std::string>>* psMaster)
{
	/*
	CalcDateSingleton* calcDate = CalcDateSingleton::getInstance();
	
	//‚V“ú‘OA‚P‚S“ú‘OAŒŽ––‚Ìchar[25]Œ^‚ð“¾‚é
	//CharFatesŒ^‚Ì\‘¢‘Ì
	CharDates charDates = calcDate->getCharDates();
	char c_lastDay[25];
	char c_before7day[25];
	char c_before14day[25];
	strcpy_s(c_lastDay, charDates.c_lastday);
	strcpy_s(c_before7day, charDates.c_before7day);
	strcpy_s(c_before14day, charDates.c_before14day);
	*/


	//TCHAR     szBuf[1024];
	TCHAR     szCol1[25]{};
	TCHAR     szCol2[25]{};
	TCHAR     szCol3[25]{};
	SQLLEN    nColLen1 = 0;
	SQLLEN    nColLen2 = 0; 
	SQLLEN    nColLen3 = 0;
	SQLRETURN nResult;


	//sprintf_s‚ðŽg‚Á‚ÄA•¶Žš‚Æ•Ï”(fromDay, tillDay)‚ðŒ‹‡‚³‚¹‚½‚¢‚Ì‚Å
	//charŒ^‚É‚·‚é
	char moji[256];
	sprintf_s(moji,
		"SELECT PsmHinCDO, PsmHinCDK, PsmInsS"
		" FROM MPSMST"
		" WHERE (PsmHinCDO >= 'GT-' AND PsmHinCDO <= 'GU-') OR" 
		" (PsmHinCDO >= 'S2-' AND PsmHinCDO <= 'S9-')"
		" ORDER BY PsmHinCDO");
	/*
	char h1[30] = "20230501";
	char h2[30] = "20240229";
	sprintf_s(moji,
		"SELECT TnkHinCD,TnkAitCD1,TnkDay,TnkTnk"
		" FROM MTANKA"
		" WHERE TnkDay>= %s AND TnkDay<= %s"
		" ORDER BY TnkHinCD,TnkAitCD1,TnkDay", h1, h2);
		*/


	//SQLExecDirect‚É“n‚·‚Ì‚ÉAwchar_t(TCHAR)Œ^‚É‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢‚©‚ç
	//mbstowcs‚ðŽg‚Á‚Ä•ÏŠ·‚·‚éBvisual studio‚ÌƒvƒƒpƒeƒB‚ÌÝ’è‚Å
	//SDLƒ`ƒFƒbƒN‚ðu‚¢‚¢‚¦v‚É‚µ‚È‚¢‚ÆŽg‚¦‚È‚¢(mbstowcs_s)‚ª„§‚³‚ê‚Ä
	//‚¢‚é‚ªAŽg‚¢•û‚ª‚í‚©‚ç‚È‚¢‚©‚ç
	TCHAR wmoji[256]{};
	mbstowcs(wmoji, moji, (sizeof wmoji) / 2);


	ConnectSql* conSql = new ConnectSql();

	SQLHSTMT hstmt = conSql->connectSql("psMaster");
	//nResult = SQLExecDirect(hstmt, (SQLTCHAR*)TEXT(
	nResult = SQLExecDirect(hstmt, (SQLTCHAR *)wmoji, SQL_NTS);


	SQLBindCol(hstmt, 1, SQL_C_TCHAR, szCol1, sizeof(szCol1), &nColLen1);
	SQLBindCol(hstmt, 2, SQL_C_TCHAR, szCol2, sizeof(szCol2), &nColLen2);
	SQLBindCol(hstmt, 3, SQL_C_TCHAR, szCol3, sizeof(szCol3), &nColLen3);


	int cnt = 0;
	for (;;) {
		nResult = SQLFetch(hstmt);
		if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO) {
			std::vector<std::string> line;
			std::wstring col1(&szCol1[0]);                   //‚±‚Ì‚Qs‚Å
			std::string strCol1(col1.begin(), col1.end());   //TCHARŒ^‚©‚çstringŒ^‚É•ÏŠ·
			std::wstring col2(&szCol2[0]);
			std::string strCol2(col2.begin(), col2.end());
			std::wstring col3(&szCol3[0]);
			std::string strCol3(col3.begin(), col3.end());
			line.push_back(strCol1);
			line.push_back(strCol2);
			line.push_back(strCol3);
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
