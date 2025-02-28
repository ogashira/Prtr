#include "CreateMaterialQty.h"
#include "IFSelectSql.h"
#include "ProcessingSqlData.h"
#include "CreateCsv.h"
#include "Printer.h"

/*
	CalcDateSingleton* myDate;
	std::map<std::string, float> mapLastYearG;
	std::map<std::string, float> mapThisYearG;
	std::map<std::string, float> mapDiffG;
	std::map<std::string, float> mpBuyG;
	*/

CreateMaterialQty::CreateMaterialQty( CalcDateSingleton* myDate) 
{
	this -> myDate = myDate;
	mapThisYearG = new std::map<std::string, float>;
	mapLastYearG = new std::map<std::string, float>;
	mapDiffG = new std::map<std::string, float>;
	mapBuyG = new std::map<std::string, float>;
	vecAllG = new std::vector<std::string>;
}

void CreateMaterialQty::createMaterialQty(std::map<std::string, float>* materialQty)
{
	ProcessingSqlData* processingSqlData = new ProcessingSqlData(
		         mapThisYearG, mapLastYearG, mapDiffG, mapBuyG, vecAllG, myDate);

	delete processingSqlData;
	this->calcMaterialQty(materialQty);


// TODO Œã‚ÅÁ‚·>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	std::vector<std::vector<std::string>> allData;
	for (std::string g : *vecAllG) {
		float thisG = 0;
		float lastG = 0;
		float diffG = 0;
		float buyG  = 0;
		if (mapThisYearG->count(g) != 0) { thisG = (*mapThisYearG)[g]; }
		if (mapLastYearG->count(g) != 0) { lastG = (*mapLastYearG)[g]; }
		if (mapDiffG->count(g)     != 0) { diffG = (*mapDiffG)[g]; }
		if (mapBuyG->count(g)      != 0) { buyG  = (*mapBuyG)[g]; }

		std::vector<std::string> line;
		line.push_back(g);
		line.push_back(std::to_string(thisG));
		line.push_back(std::to_string(lastG));
		line.push_back(std::to_string(diffG));
		line.push_back(std::to_string(buyG));
		allData.push_back(line);
	}
	
	std::string col = "Œ´—¿•i”Ô,¡”NÝŒÉkg,‹Ž”NÝŒÉkg,GTŒ´—¿·kg,w”ƒŒ´—¿kg";
	std::string path = "./materialAllQty.csv";
	CreateCsv createCsv;
	createCsv.toCsv(&allData, &col, &path);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	delete mapThisYearG;
	delete mapLastYearG;
	delete mapDiffG;
	delete mapBuyG;
	delete vecAllG;

}

void CreateMaterialQty::calcMaterialQty(std::map<std::string, float>* prtrData) {

	for (std::string g : *vecAllG) {
		float thisG = 0;
		float lastG = 0;
		float diffG = 0;
		float buyG  = 0;
		if (mapThisYearG->count(g) != 0) { thisG = (*mapThisYearG)[g]; }
		if (mapLastYearG->count(g) != 0) { lastG = (*mapLastYearG)[g]; }
		if (mapDiffG->count(g)     != 0) { diffG = (*mapDiffG)[g]; }
		if (mapBuyG->count(g)      != 0) { buyG  = (*mapBuyG)[g]; }

		(*prtrData)[g] = lastG + buyG - thisG + diffG;
	}
}
