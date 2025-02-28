#include "CalcDateSingleton.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>


//���̈�s�������ƃr���h���ʂ�Ȃ�??
CalcDateSingleton* CalcDateSingleton::instance = nullptr;

CalcDateSingleton::CalcDateSingleton() {
	myYear = "0";
	strToday = this->calcStrToday();
	strBefore7day = this->calcStrBefore7day();
	strBefore14day = this->calcStrBefore14day();
	strLastDay = this->calcStrLastDayOfThisMonth();
};

CalcDateSingleton::~CalcDateSingleton() {
};

void CalcDateSingleton::setMyYear(std::string myYear) {
	this->myYear = myYear;
}

//staticMethod
CalcDateSingleton* CalcDateSingleton::getInstance() {
	if (instance == nullptr) {
		instance = new CalcDateSingleton();
	}
	return instance;
}

std::string CalcDateSingleton::returnStrToday() { return strToday; }

std::string CalcDateSingleton::returnStrLastDay() { return strLastDay; }

std::string CalcDateSingleton::calcStrToday() {

	struct mytm {
		int tm_mday;
		int tm_mon;
		int tm_year;
	};

	time_t t = time(nullptr);
	const tm* now = localtime(&t);

	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;


	strToday = toStrDate(year, month, day);

	//char buffer[128];
	//strftime(buffer, sizeof(buffer), "%Y%m%d", log);
	return strToday;
}

std::string CalcDateSingleton::calcStrBefore7day() {
	std::string strYear = strToday.substr(0, 4);
	std::string strMonth = strToday.substr(4, 2);
	std::string strDay = strToday.substr(6, 2);

	int year = std::stoi(strYear);
	int month = std::stoi(strMonth);
	int day = std::stoi(strDay);
	int before7y{};
	int before7m{};
	int before7d{};

	//day���W�ȏゾ������day����7�������ďI���B
	if (day > 7) {
		before7d = day - 7;
		before7y = year;
		before7m = month;
		return toStrDate(before7y, before7m, before7d);
	}
	//day��7�ȉ��̏ꍇ��day-7�ɐ挎�̖����𑫂���before7d�����܂�
	if (month == 1) { before7d = getLastDayOfMonth(year - 1, 12) + (day - 7); }
	else { before7d = getLastDayOfMonth(year, month - 1) + (day - 7);}

	
	//month��1�̏ꍇ��before7m��12�ɂ��āAyear-1���s��
	if (month == 1) { 
		before7m = 12; 
		before7y = year - 1; 
		return toStrDate(before7y, before7m, before7d);
	}

	//day��7�ȉ���month��2�ȏ�̏ꍇ��month-1
	before7m = month - 1;
	before7y = year;
	return toStrDate(before7y, before7m, before7d);
}

std::string CalcDateSingleton::calcStrBefore14day() {
	std::string strYear = strToday.substr(0, 4);
	std::string strMonth = strToday.substr(4, 2);
	std::string strDay = strToday.substr(6, 2);

	int year = std::stoi(strYear);
	int month = std::stoi(strMonth);
	int day = std::stoi(strDay);
	int before14y{};
	int before14m{};
	int before14d{};

	//day��15�ȏゾ������day����14�������ďI���B
	if (day > 15) {
		before14d = day - 14;
		before14y = year;
		before14m = month;
		return toStrDate(before14y, before14m, before14d);
	}
	//day��14�ȉ��̏ꍇ��day-14�ɐ挎�̖����𑫂���before14d�����܂�
	if (month == 1) { before14d = getLastDayOfMonth(year - 1, 12) + (day - 14); }
	else { before14d = getLastDayOfMonth(year, month - 1) + (day - 14);}

	
	//month��1�̏ꍇ��before14m��12�ɂ��āAyear-1���s��
	if (month == 1) { 
		before14m = 12; 
		before14y = year - 1; 
		return toStrDate(before14y, before14m, before14d);
	}

	//day��14�ȉ���month��2�ȏ�̏ꍇ��month-1
	before14m = month - 1;
	before14y = year;
	return toStrDate(before14y, before14m, before14d);
}

std::string CalcDateSingleton::calcStrLastDayOfThisMonth() {
	std::string strYear = strToday.substr(0, 4);
	std::string strMonth = strToday.substr(4, 2);
	std::string strDay = strToday.substr(6, 2);

	int lastDay = getLastDayOfMonth(std::stoi(strYear), std::stoi(strMonth));

	return strYear + strMonth + std::to_string(lastDay);

}

bool CalcDateSingleton::isLeapYear(int year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) {
		return true;
	}
	return false;
}

int CalcDateSingleton::getLastDayOfMonth(int year, int month) {
	int leapDays[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int nonLeapDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool isleap = isLeapYear(year);

	if (isleap) { return leapDays[month - 1]; }

	return nonLeapDays[month - 1];
}

std::string CalcDateSingleton::toStrDate(int year, int month, int day) {
	std::string strYear = std::to_string(year);
	std::string strMonth = std::to_string(month);
	std::string strDay = std::to_string(day);
	if (month <= 9) { strMonth = '0' + std::to_string(month); }
	if (day <= 9) { strDay = '0' + std::to_string(day); }

	return strYear + strMonth + strDay;
}

void CalcDateSingleton::showDate(){
	strFebruaryLastYear = calcStrFebruaryLastYear();
	strFebruaryThisYear = calcStrFebruaryThisYear();
	strSttDay = calcStrSttDay();
	strEndDay = calcStrEndDay();

	std::cout << "����          : " << strToday << std::endl;
	std::cout << "7���O         : " << strBefore7day << std::endl;
	std::cout << "14���O        : " << strBefore14day << std::endl;
	std::cout << "������        : " << strLastDay << std::endl;
	std::cout << "������N�Q��  : " << strFebruaryLastYear << std::endl;
	std::cout << "�����N�Q��    : " << strFebruaryThisYear << std::endl;
	std::cout << "�w�������J�n��: " << strSttDay << std::endl;
	std::cout << "�w�������ŏI��: " << strEndDay << std::endl;
}

std::string CalcDateSingleton::calcStrFebruaryLastYear(){
	std::string lastY = std::to_string(std::stoi(myYear) - 1);
	return lastY + "02";
}
std::string CalcDateSingleton::calcStrFebruaryThisYear() { 
	std::string thisY = myYear;
	return thisY + "02";
}
std::string CalcDateSingleton::calcStrSttDay(){ 
	std::string lastY = std::to_string(std::stoi(myYear) - 1);
	return lastY + "03" + "01";
}
std::string CalcDateSingleton::calcStrEndDay(){
	std::string thisY = myYear;
	bool isLeap = this->isLeapYear(std::stoi(thisY));
	if (isLeap) { return thisY + "02" + "29"; }
	return thisY + "02" + "28";
}

