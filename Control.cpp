#include "Control.h"
#include "CalcDateSingleton.h"
#include "UserInterface.h"
#include <iostream>
#include "Test.h"
#include "CreateMaterialQty.h"
#include "CreateCsv.h"
#include "CreatePrtrData.h"


int Control::start() {
	UserInterface *ui = new UserInterface;
	CalcDateSingleton *singleton = CalcDateSingleton::getInstance();

	try {
		ui->startChat(singleton);
	}
	//ここはstd::string sではキャッチしてくれない
	catch(const char* s){
		std::cout << s << std::endl;
		delete singleton;
		delete ui;
		return 0;
	}

	std::string myYear = ui->getMyYear();

	//singletonにmyYearをセット
	singleton->setMyYear(myYear);
	delete ui;


	CreateMaterialQty materialQty(singleton);
	materialQty.createMaterialQty(&mapMaterialQty);

	CreatePrtrData createPrtrData(&prtrData, &mapMaterialQty);
	createPrtrData.createPrtrData();

	std::string path;
	std::string col;

	CreateCsv createCsv;
	path = "./materialQty.csv";
	col = "原料品番,PRTR移動量(Kg)";
	createCsv.toCsv(&mapMaterialQty, &col, &path);

	path = "./prtrdata.csv";
	col = "prtrCD,取扱い量(t),排出量(kg)";
	createCsv.toCsv(&prtrData, &col, &path);

	std::cout << std::endl;
	std::cout << "プログラム終了です。" << std::endl;
	std::cout << "カレントディレクトリにcsvファイルを作成しました。" << std::endl;

	

	delete singleton;
	return 0;
}
