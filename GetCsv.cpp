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
    delimiter : 区切り文字(カンマなど)
    *row は関数内でdeleteされるが、returnするresultは呼び出し元で
	deleteする必要がある
    */
	std::ifstream ifs(path);
	std::string line;
	std::string field;
	std::vector<std::vector<std::string>>* result =
		new std::vector<std::vector<std::string>>();

	while (getline(ifs, line)) {
		//[,]区切りごとにデータを読み込むためにistringstream型にする
		std::istringstream stream(line);
		std::vector<std::string>* row = new std::vector<std::string>();
		//[,]区切りごとにデータを読み込む
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
	vector<vector<string>> のポインタをもらってcsvファイルの内容に
	中身を書き換える
	*/
	std::ifstream ifs(path);
	std::string line;
	std::string field;

	while (getline(ifs, line)) {
		//[,]区切りごとにデータを読み込むためにistringstream型にする
		std::istringstream stream(line);
		std::vector<std::string>* row = new std::vector<std::string>;
		//[,]区切りごとにデータを読み込む
		while (getline(stream, field, delimiter)) {
			row->push_back(field);
		}
		csvData->push_back(*row);
		delete row;
	}
}


