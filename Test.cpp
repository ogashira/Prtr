#include "Test.h"
#include "GtComponent.h"
#include "SelectBuyMaterial.h"
#include "SelectTehai.h"
#include "IFSelectSql.h"
#include "SelectZaikoThisYear.h"
#include "SelectZaikoLastYear.h"
#include "CreateMapTani.h"
#include "UserInterface.h"
#include "ChangeToKg.h"
#include <iostream>


Test::Test(CalcDateSingleton* myDate) {
	this->myDate = myDate;
}

Test::~Test() {
}

int Test::start() {

	std::vector<std::vector<std::string>> zaikoVecThisYear;
	std::vector<std::vector<std::string>> zaikoVecLastYear;
	IFSelectSql* zaikothis = new SelectZaikoThisYear(myDate);
	IFSelectSql* zaikolast = new SelectZaikoLastYear(myDate);
	zaikothis->ExecuteStatement(&zaikoVecThisYear);
	zaikolast->ExecuteStatement(&zaikoVecLastYear);

	Printer printer;
	printer.printScreen(&zaikoVecThisYear);
	std::cout << "*********************************************"<< std::endl;
	printer.printScreen(&zaikoVecLastYear);
	
	delete zaikothis;
	delete zaikolast;

	return 0;
}


int Test::start2() {

	std::vector<std::vector<std::string>> zaiko;
	IFSelectSql* instance = new SelectBuyMaterial(myDate);
	instance->ExecuteStatement(&zaiko);

	Printer printer;
	printer.printScreen(&zaiko);

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "-----------------------------------" << std::endl;

	ChangeToKg change;
	change.toKgByKobaiTani(&zaiko);
	printer.printScreen(&zaiko);


	delete instance;

	return 0;
}

int Test::start3() {
	GtComponent com;
	return 0;
}

