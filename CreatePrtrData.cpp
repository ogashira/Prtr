#include <iostream>
#include "CreatePrtrData.h"
#include "Printer.h"

/*
private:
	std::vector<std::vector<std::string>>* prtrData;
	std::map<std::string, float>* mapMaterialQty;
	std::map<std::string, float>* mapPrtrQty;
	std::map<std::string, float>* mapPrtrEmissionFactor;
public:
	CreatePrtrData(
		std::vector<std::vector<std::string>>* prtrData,
		std::map<std::string, float>* mapMaterialQty
	);
	void createPrtrData();

private:
	void createMapPrtrQty(GetCsv* getCsv);
	void createMapPrtrEmissionFactor(GetCsv* getCsv);
*/

CreatePrtrData::CreatePrtrData(
	std::vector<std::vector<std::string>>* prtrData,
	std::map<std::string, float>* mapMaterialQty
) {
	this->prtrData = prtrData;
	this->mapMaterialQty = mapMaterialQty;
	mapPrtrQty = new std::map<std::string, float>();
	mapPrtrEmissionFactor = new std::map<std::string, float>();
}
CreatePrtrData::~CreatePrtrData() {
	delete mapPrtrQty;
	delete mapPrtrEmissionFactor;
}

void CreatePrtrData::createPrtrData() {
	GetCsv* getCsv = new GetCsv();
	createMapPrtrQty(getCsv);
	createMapPrtrEmissionFactor(getCsv);
	delete getCsv;

	for (auto iter = mapPrtrEmissionFactor->begin(); 
		                   iter != mapPrtrEmissionFactor->end(); iter++) {
		std::string prtrCd = iter->first;
		float prtrQty = 0.0f;
		float prtrEmission = 0.0f;
		if (mapPrtrQty->count(prtrCd)) { prtrQty = (*mapPrtrQty)[prtrCd]; }
		prtrEmission = (*mapPrtrEmissionFactor)[prtrCd] * prtrQty * 1000;

		std::vector<std::string> line;
		line.push_back(prtrCd);
		line.push_back(std::to_string(prtrQty));
		line.push_back(std::to_string(prtrEmission));

		prtrData->push_back(line);
	}

	Printer printer;
	printer.printScreen(prtrData);


}
void CreatePrtrData::createMapPrtrQty(GetCsv* getCsv) {
	std::vector<std::vector<std::string>>* vecPrtrContent
		              = new std::vector<std::vector<std::string>>();
	std::string path = 
	"//192.168.1.247/‹¤—L/‹Zp‰ÛÌ«ÙÀÞ/200. effit_data/Ï½À/prtrŠÖ˜A/prtrŠÜ—L—Ê.csv";
	getCsv->getCsv(vecPrtrContent, path, ',');

	for (std::vector<std::string> line : *vecPrtrContent) {
		if (mapMaterialQty->count(line[0])) {
			if (mapPrtrQty->count(line[1])) {
				(*mapPrtrQty)[line[1]] = (*mapPrtrQty)[line[1]] + 
					                     ((*mapMaterialQty)[line[0]] * 
					                      std::stof(line[2])) / 1000; //ƒgƒ“‚É•ÏŠ·
			}
			else {
				(*mapPrtrQty)[line[1]] = ((*mapMaterialQty)[line[0]] * 
					                      std::stof(line[2])) / 1000; //ƒgƒ“‚É•ÏŠ·
			}
		}
	}

	delete vecPrtrContent;
}
void CreatePrtrData::createMapPrtrEmissionFactor(GetCsv* getCsv) {
	std::vector<std::vector<std::string>>* vecPrtrEmissionFactor
		              = new std::vector<std::vector<std::string>>();
	std::string path = 
	"//192.168.1.247/‹¤—L/‹Zp‰ÛÌ«ÙÀÞ/200. effit_data/Ï½À/prtrŠÖ˜A/prtrŒW”.csv";
	getCsv->getCsv(vecPrtrEmissionFactor, path, ',');

	for (std::vector<std::string> line : *vecPrtrEmissionFactor) {
		if (line[0] == "prtrCD") { continue; }
		(*mapPrtrEmissionFactor)[line[0]] = std::stof(line[4]);
	}

	delete vecPrtrEmissionFactor;
}
