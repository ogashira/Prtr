#ifndef _CALCDATESINGLETON_H_
#define _CALCDATESINGLETON_H_

#include <string>

class CalcDateSingleton
{
private:

	static CalcDateSingleton* instance;
	CalcDateSingleton(); 

	std::string myYear;               //���[�U�[�����͂����N("2024" �Ȃ�)
	std::string strToday;
	std::string strBefore7day;
	std::string strBefore14day;
	std::string strLastDay;
	std::string strFebruaryLastYear;  //202302�@ ������N�Q�����_�̍݌ɗ�
	std::string strFebruaryThisYear;  //202402�@ �����N�Q�����_�̍݌ɗ�
	std::string strSttDay;            //20230301 �w�������͈͎̔n�� 
	std::string strEndDay;            //20240229 �w�������͈̔͏I���

	bool isLeapYear(int);
	std::string calcStrToday();
	std::string calcStrBefore7day();
	std::string calcStrBefore14day();
	std::string calcStrLastDayOfThisMonth();
	int getLastDayOfMonth(int, int);
	std::string toStrDate(int, int, int);

public:
	~CalcDateSingleton();

	static CalcDateSingleton* getInstance();

	std::string returnStrLastDay();
	std::string returnStrToday();
	std::string calcStrFebruaryLastYear();
	std::string calcStrFebruaryThisYear();
	std::string calcStrSttDay();
	std::string calcStrEndDay();
	void showDate();
	void setMyYear(std::string myYear);

};

#endif //_CALCDATESINGLETON_H_
