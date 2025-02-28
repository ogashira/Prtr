#include "Printer.h"
#include <iostream>
#include <regex>

void Printer::printScreen(std::vector<std::vector<std::string>>* master)
{
	for (int i = 0; i < (*master).size(); i++) {
		for (int j = 0; j < (*master)[i].size()-1; j++) {
			std::cout << (*master)[i][j] << ",";
			//printf("%-25s", (*master)[i][j].c_str());
		}
		std::cout << (*master)[i][(*master)[i].size()-1] << std::endl;
	}
}

void Printer::printScreen(std::vector<std::string>* master)
{
	for (int i = 0; i < (*master).size(); i++) {
			std::cout << (*master)[i] << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, std::string>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, int>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, float>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second << std::endl;
	}
}

void Printer::printScreen(std::map<std::string, std::vector<std::string>>* master) {

	for (auto iter = master->begin(); iter != master->end(); iter++) {
		std::cout << iter->first << "=>" << iter->second[0] << ","
			                             << iter->second[1] << "," 
			                             << iter->second[2] << ","
			                             << std::endl;
	}
}

void Printer::printfScreen(std::vector<std::vector<std::string>>* master)
{
	char cstr0[25];
	char cstr1[25];
	char cstr2[25];
	char cstr3[25];
	char cstr4[25];
	char cstr5[25];
	char cstr6[25];


	printf("%s\n", "======================================================================================|");
	printf("%-25s|%-7s|%-12s|%-15s|%7s|%7s|%7s|\n", "•i”Ô","‘qŒÉ","Lot","Œ“ú","İŒÉ","o‰×","»‘¢");
	printf("%s\n", "======================================================================================|");


	for (int i = 0; i < master->size() -1; i++) {
		convertToFloat((&(*master)[i][0]), cstr0); 
		convertToFloat((&(*master)[i][1]), cstr1); 
		//convertToFloat((&(*master)[i][2]), cstr2); 
		strcpy_s(cstr2, (*master)[i][2].size() + 1, (*master)[i][2].c_str());
		//convertToFloat((&(*master)[i][3]), cstr3); 
		strcpy_s(cstr3, (*master)[i][3].size() + 1, (*master)[i][3].c_str());
		convertToFloat((&(*master)[i][4]), cstr4); 
		convertToFloat((&(*master)[i][5]), cstr5); 
		convertToFloat((&(*master)[i][6]), cstr6); 

		printf("%-25s|%-7s|%-12s|%-15s|%7s|%7s|%7s|\n", cstr0, cstr1, cstr2, cstr3, cstr4, cstr5, cstr6);

		if ((*master)[i][0] != (*master)[i + 1][0]){
			printf("%s\n", "-------------------------+-------+------------+---------------+-------+-------+-------|");
		}
	}
	convertToFloat((&(*master)[master->size()-1][0]), cstr0);
	convertToFloat((&(*master)[master->size()-1][1]), cstr1); 
	strcpy_s(cstr2, (*master)[master->size()-1][2].size() + 1, (*master)[master->size()-1][2].c_str());
	strcpy_s(cstr3, (*master)[master->size()-1][3].size() + 1, (*master)[master->size()-1][3].c_str());
	convertToFloat((&(*master)[master->size()-1][4]), cstr4); 
	convertToFloat((&(*master)[master->size()-1][5]), cstr5); 
	convertToFloat((&(*master)[master->size()-1][6]), cstr6); 

	printf("%-25s|%-7s|%-12s|%-15s|%7s|%7s|%7s|\n", cstr0, cstr1, cstr2, cstr3, cstr4, cstr5, cstr6);

	printf("%s\n", "--------------------------------------------------------------------------------------|");
}

int Printer::convertToFloat(std::string* str, char* cstr) {
	std::regex reNum(R"([+-]?\d+(?:\.\d+)?)");

	if (std::regex_match(*str, reNum)) {
		std::sprintf(cstr, "%d", std::stoi(*str));
	}
	else {
		strcpy_s(cstr, (*str).size()+1, (*str).c_str());
	}
	return 0;
}
