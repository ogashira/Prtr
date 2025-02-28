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
	//������std::string s�ł̓L���b�`���Ă���Ȃ�
	catch(const char* s){
		std::cout << s << std::endl;
		delete singleton;
		delete ui;
		return 0;
	}

	std::string myYear = ui->getMyYear();

	//singleton��myYear���Z�b�g
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
	col = "�����i��,PRTR�ړ���(Kg)";
	createCsv.toCsv(&mapMaterialQty, &col, &path);

	path = "./prtrdata.csv";
	col = "prtrCD,�戵����(t),�r�o��(kg)";
	createCsv.toCsv(&prtrData, &col, &path);

	std::cout << std::endl;
	std::cout << "�v���O�����I���ł��B" << std::endl;
	std::cout << "�J�����g�f�B���N�g����csv�t�@�C�����쐬���܂����B" << std::endl;

	

	delete singleton;
	return 0;
}
