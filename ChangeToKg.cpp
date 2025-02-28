#include "ChangeToKg.h"
#include "CreateMapTani.h"
#include "Printer.h"
#include <iostream>

ChangeToKg::ChangeToKg() {
	mapKanriTani = new std::map<std::string, std::string>;
	mapKobaiTani = new std::map<std::string, std::vector<std::string>>;
	
	CreateMapTani* mapTani = new CreateMapTani();
	mapTani->createMapKanriTani(mapKanriTani);
	mapTani->createMapKobaiTani(mapKobaiTani);
	delete mapTani;
}

ChangeToKg::~ChangeToKg()
{
	delete mapKanriTani;
	delete mapKobaiTani;
}


void ChangeToKg::toKgByKanriTani(std::vector<std::vector<std::string>>* zaiko) {
	for (int i = 0; i < zaiko->size(); i++) {
		if ((*mapKanriTani).count((*zaiko)[i][0]) != 0) {
			if ((*mapKanriTani)[(*zaiko)[i][0]] == "G") {
				//std::vector<std::string>* newLine = new std::vector<std::string>;
				//newLine->push_back(line[0]);
				//newLine->push_back(std::to_string(std::stof(line[1]) / 1000));
				//zaikoKg->push_back(*newLine);
				//delete newLine;
				(*zaiko)[i][1] = std::to_string(std::stof((*zaiko)[i][1]) / 1000);
			}
		}
	}
}

void ChangeToKg::toKgByKobaiTani(std::vector<std::vector<std::string>>* zaiko) {
	for (int i = 0; i < zaiko->size(); i++) {
		if ((*mapKobaiTani).count((*zaiko)[i][0]) != 0) {
			if ((*mapKobaiTani)[(*zaiko)[i][0]][0] == "G") {
				(*zaiko)[i][1] = std::to_string(std::stof((*zaiko)[i][1]) / 1000);
			}
			else if ((*mapKobaiTani)[(*zaiko)[i][0]][0] == "L") {
				(*zaiko)[i][1] = std::to_string(std::stof((*zaiko)[i][1]) * 
					(std::stof((*mapKobaiTani)[(*zaiko)[i][0]][1]) / 
				   	std::stof((*mapKobaiTani)[(*zaiko)[i][0]][2])));
			}
		}
	}
}
