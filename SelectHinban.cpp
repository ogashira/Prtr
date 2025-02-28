#include "SelectHinban.h"

void SelectHinban::ExecuteStatement(
	std::vector<std::vector<std::string>>* psMaster)
{
	//TCHAR     szBuf[1024];
	TCHAR     szCol1[25]{};
	TCHAR     szCol2[25]{};
	SQLLEN    nColLen1 = 0;
	SQLLEN    nColLen2 = 0;
	SQLRETURN nResult;


	//sprintf_s���g���āA�����ƕϐ�(fromDay, tillDay)���������������̂�
	//char�^�ɂ���
	char moji[256];
	sprintf_s(moji,
		"SELECT HinHinCD, HinTniCD"
		" FROM MHINCD"
		" WHERE HinMokCD1 = 'G0' OR HinMokCD1 = 'GT'"
		" ORDER BY HinHinCD");
	/*
	char h1[30] = "20230501";
	char h2[30] = "20240229";
	sprintf_s(moji,
		"SELECT TnkHinCD,TnkAitCD1,TnkDay,TnkTnk"
		" FROM MTANKA"
		" WHERE TnkDay>= %s AND TnkDay<= %s"
		" ORDER BY TnkHinCD,TnkAitCD1,TnkDay", h1, h2);
		*/


		//SQLExecDirect�ɓn���̂ɁAwchar_t(TCHAR)�^�ɂ��Ȃ��Ƃ����Ȃ�����
		//mbstowcs���g���ĕϊ�����Bvisual studio�̃v���p�e�B�̐ݒ��
		//SDL�`�F�b�N���u�������v�ɂ��Ȃ��Ǝg���Ȃ�(mbstowcs_s)�����������
		//���邪�A�g�������킩��Ȃ�����
	TCHAR wmoji[256]{};
	mbstowcs(wmoji, moji, (sizeof wmoji) / 2);


	ConnectSql* conSql = new ConnectSql();

	SQLHSTMT hstmt = conSql->connectSql("hinbanMaster");
	//nResult = SQLExecDirect(hstmt, (SQLTCHAR*)TEXT(
	nResult = SQLExecDirect(hstmt, (SQLTCHAR*)wmoji, SQL_NTS);


	SQLBindCol(hstmt, 1, SQL_C_TCHAR, szCol1, sizeof(szCol1), &nColLen1);
	SQLBindCol(hstmt, 2, SQL_C_TCHAR, szCol2, sizeof(szCol2), &nColLen2);


	int cnt = 0;
	for (;;) {
		nResult = SQLFetch(hstmt);
		if (nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO) {
			std::vector<std::string> line;
			std::wstring col1(&szCol1[0]);                   //���̂Q�s��
			std::string strCol1(col1.begin(), col1.end());   //TCHAR�^����string�^�ɕϊ�
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

