#ifndef _CALCDATESINGLETON_H_
#define _CALCDATESINGLETON_H_

#include <string>

class CalcDateSingleton
{
private:

	static CalcDateSingleton* instance;
	CalcDateSingleton(); 

	std::string myYear;               //ユーザーが入力した年("2024" など)
	std::string strToday;
	std::string strBefore7day;
	std::string strBefore14day;
	std::string strLastDay;
	std::string strFebruaryLastYear;  //202302　 調査昨年２月時点の在庫量
	std::string strFebruaryThisYear;  //202402　 調査年２月時点の在庫量
	std::string strSttDay;            //20230301 購入原料の範囲始め 
	std::string strEndDay;            //20240229 購入原料の範囲終わり

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
