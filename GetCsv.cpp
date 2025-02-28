#include "GetCsv.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


GetCsv::GetCsv(){};
GetCsv::~GetCsv(){};

std::vector<std::vector<std::string>>* GetCsv::getCsv(std::string path, 
	                                                           char delimiter) {
    /*
    delimiter : ��؂蕶��(�J���}�Ȃ�)
    *row �͊֐�����delete����邪�Areturn����result�͌Ăяo������
	delete����K�v������
    */
	std::ifstream ifs(path);
	std::string line;
	std::string field;
	std::vector<std::vector<std::string>>* result =
		new std::vector<std::vector<std::string>>();

	while (getline(ifs, line)) {
		//[,]��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
		std::istringstream stream(line);
		std::vector<std::string>* row = new std::vector<std::string>();
		//[,]��؂育�ƂɃf�[�^��ǂݍ���
		while (getline(stream, field, delimiter)) {
			row->push_back(field);
		}
		result->push_back(*row);
		delete row;
	}
	return result;
}

void GetCsv::getCsv(std::vector<std::vector<std::string>>* csvData, 
	                                       std::string path, char delimiter) {
	/* 
	vector<vector<string>> �̃|�C���^���������csv�t�@�C���̓��e��
	���g������������
	*/
	std::ifstream ifs(path);
	std::string line;
	std::string field;

	while (getline(ifs, line)) {
		//[,]��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
		std::istringstream stream(line);
		std::vector<std::string>* row = new std::vector<std::string>;
		//[,]��؂育�ƂɃf�[�^��ǂݍ���
		while (getline(stream, field, delimiter)) {
			row->push_back(field);
		}
		csvData->push_back(*row);
		delete row;
	}
}


