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

	std::cout << "PRTR�f�[�^��o�N����͂��Ă�������(��: 2024)" << std::endl;
	std::cout << ": ";
	std::cin >> myYear;
	//��������啶���ɕϊ�����
	std::transform(myYear.cbegin(), myYear.cend(), 
		                                        myYear.begin(), toupper);

	if (!std::regex_match(myYear, std::regex(R"(^[1-9]+\.*[0-9]*$)"))) {
		throw "���͂��������͐��l�ł͂���܂���";
		//Controller::start()�ɓ�����
	}
	if (!((int)myYear.length() == 4)) {
		throw "���͂��������͔N�ł͂���܂���";
		//Controller::start()�ɓ�����
	}
	if (std::stoi(myYear) > std::stoi(strYear)) {
		throw "�����̃f�[�^�͌v�Z�ł��܂���";
	}
	if (std::stoi(myYear) == std::stoi(strYear)) {
		std::string tanaorosiDay = myYear + "03" + "17";
		if (std::stoi(strToday) <= std::stoi(tanaorosiDay)) {
			throw "���N�̂Q���̒I���f�[�^�͂R���P�V���ȍ~�ł�";
		}
	}
	if (std::stoi(myYear) < 2010) {
			throw "2010�N�ȑO�̃f�[�^�͌v�Z�ł��܂���";
	}
}

std::string UserInterface::getMyYear() 
{
	return myYear;
}
