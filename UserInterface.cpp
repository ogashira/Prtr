#include "UserInterface.h"
#include "SelectHinban.h"
#include <algorithm>
#include <cstdio>
#include <regex>
#include<iostream>




void UserInterface::startChat(CalcDateSingleton* myDate)
{
	std::string strToday = myDate->returnStrToday();
	std::string strYear = strToday.substr(0, 4);

	std::cout << "PRTRデータ提出年を入力してください(例: 2024)" << std::endl;
	std::cout << ": ";
	std::cin >> myYear;
	//小文字を大文字に変換する
	std::transform(myYear.cbegin(), myYear.cend(), 
		                                        myYear.begin(), toupper);

	if (!std::regex_match(myYear, std::regex(R"(^[1-9]+\.*[0-9]*$)"))) {
		throw "入力した文字は数値ではありません";
		//Controller::start()に投げる
	}
	if (!((int)myYear.length() == 4)) {
		throw "入力した文字は年ではありません";
		//Controller::start()に投げる
	}
	if (std::stoi(myYear) > std::stoi(strYear)) {
		throw "未来のデータは計算できません";
	}
	if (std::stoi(myYear) == std::stoi(strYear)) {
		std::string tanaorosiDay = myYear + "03" + "17";
		if (std::stoi(strToday) <= std::stoi(tanaorosiDay)) {
			throw "今年の２月の棚卸データは３月１７日以降です";
		}
	}
	if (std::stoi(myYear) < 2010) {
			throw "2010年以前のデータは計算できません";
	}
}

std::string UserInterface::getMyYear() 
{
	return myYear;
}
