#include "ProcessingSqlData.h"
#include "Printer.h"
#include "IFSelectSql.h"
#include "SelectHinban.h"
#include "SelectZaikoThisYear.h"
#include "SelectZaikoLastYear.h"
#include "SelectBuyMaterial.h"
#include "ChangeToKg.h"
#include "GtComponent.h"
#include "GetCsvHinban.h"
#include <regex>
#include <iostream>
#include "GetCsvZaikoThisYear.h"
#include "GetCsvZaikoLastYear.h"
#include "GetCsvBuyMaterial.h"

ProcessingSqlData::ProcessingSqlData
(
	std::map<std::string, float>* mapThisYearG,
	std::map<std::string, float>* mapLastYearG,
	std::map<std::string, float>* mapDiffG,
	std::map<std::string, float>* mapBuyG,
	std::vector<std::string>* vecAllG,
	CalcDateSingleton* myDate
)
{
	this->mapThisYearG = mapThisYearG;
	this->mapLastYearG = mapLastYearG;
	this->mapDiffG     = mapDiffG;
	this->mapBuyG      = mapBuyG;
	this->vecAllG      = vecAllG;
	this->myDate       = myDate;

	//品番マスターからvecAllGとvecAllGtを求めておく
	//vecAllGはCreatePrtrDataかた渡ってきた。
	// vecAllGtはデストラクタでdeleteする
	vecAllGt = new std::vector<std::string>;
	this->getVecAllGAndGt();


	//SQLserverから在庫データ、購買データをダウンロード
	std::vector<std::vector<std::string>>* thisYearZaiko
					= new std::vector<std::vector<std::string>>;
	std::vector<std::vector<std::string>>* lastYearZaiko
					= new std::vector<std::vector<std::string>>;
	std::vector<std::vector<std::string>>* buyMaterials 
					= new std::vector<std::vector<std::string>>;

	this->downloadFromSql(thisYearZaiko, lastYearZaiko, buyMaterials);


	//各在庫がKG単位になる
	this->changeToKg(thisYearZaiko, lastYearZaiko, buyMaterials);

	//zaikoをGとGTに分ける
	std::vector<std::vector<std::string>>* thisYearG
					= new std::vector<std::vector<std::string>>;
	std::vector<std::vector<std::string>>* thisYearGt
					= new std::vector<std::vector<std::string>>;
	std::vector<std::vector<std::string>>* lastYearG
					= new std::vector<std::vector<std::string>>;
	std::vector<std::vector<std::string>>* lastYearGt
					= new std::vector<std::vector<std::string>>;

	this->separate(thisYearZaiko, thisYearG, thisYearGt,
		           lastYearZaiko, lastYearG, lastYearGt);
	delete thisYearZaiko;
	delete lastYearZaiko;

	// vecをmapに変更する mapThisYearG, mapLastYearG, mapBuyGは
	// CreatePrtrDataから渡ってきたmap
	std::map<std::string, float>* mapThisYearGt = new std::map<std::string, float>;
	std::map<std::string, float>* mapLastYearGt = new std::map<std::string, float>;
	this->vecToMap(thisYearG,     0, 1, mapThisYearG);
	this->vecToMap(thisYearGt,    0, 1, mapThisYearGt);
	this->vecToMap(lastYearG,     0, 1, mapLastYearG);
	this->vecToMap(lastYearGt,    0, 1, mapLastYearGt);
	this->vecToMap(buyMaterials,  0, 1, mapBuyG);

	delete thisYearG;
	delete thisYearGt;
	delete lastYearG;
	delete lastYearGt;
	delete buyMaterials;


	//diffGtを求める
	std::map<std::string, float>* mapDiffGt
		                              = new std::map<std::string, float>;
	this->gtMinusGt(mapThisYearGt, mapLastYearGt, mapDiffGt);

	delete mapThisYearGt;
	delete mapLastYearGt;
	
	//mapDiffGtをmapDiffGに変換する
	this->gtToG(mapDiffGt, mapDiffG);
	delete mapDiffGt;
}

ProcessingSqlData::~ProcessingSqlData() {
	delete vecAllGt;
}

void ProcessingSqlData::getVecAllGAndGt() {
	std::vector<std::vector<std::string>>* hinbanMaster =
						new std::vector<std::vector<std::string>>;
	IFSelectSql* sql = new SelectHinban;
	//std::string path =
		//"./csvData/hinban.csv";
	//IFSelectSql* sql = new GetCsvHinban(&path);
	sql->ExecuteStatement(hinbanMaster);

	std::regex reG(R"(^G-.*$)");
	std::regex reGT(R"(^(GT-|GTS-).*$)");

	for (std::vector<std::string> line : *hinbanMaster) {
		if (std::regex_match(line[0], reG)) {
			vecAllG->push_back(line[0]);
		}
		if (std::regex_match(line[0], reGT)) {
			vecAllGt->push_back(line[0]);
		}
	}

	delete sql;
	delete hinbanMaster;
}

void ProcessingSqlData::downloadFromSql(
	std::vector<std::vector<std::string>>* thisYearZaiko,
	std::vector<std::vector<std::string>>* lastYearZaiko,
	std::vector<std::vector<std::string>>* buyMaterials
)
{
	IFSelectSql* zaikoThis = new SelectZaikoThisYear(myDate);
	IFSelectSql* zaikoLast = new SelectZaikoLastYear(myDate);
	IFSelectSql* zaikoBuy = new SelectBuyMaterial(myDate);
	//std::string path; 
	//path =
		//"./csvData/zaikoThisYear.csv";
	//IFSelectSql* zaikoThis = new GetCsvZaikoThisYear(&path);
	//path =
		//"./csvData/zaikoLastYear.csv";
	//IFSelectSql* zaikoLast = new GetCsvZaikoLastYear(&path);
	//path =
		//"./csvData/buyMaterial.csv";
	//IFSelectSql* zaikoBuy = new GetCsvBuyMaterial(&path);

	zaikoThis->ExecuteStatement(thisYearZaiko);
	zaikoLast->ExecuteStatement(lastYearZaiko);
	zaikoBuy->ExecuteStatement(buyMaterials);

	delete zaikoThis;
	delete zaikoLast;
	delete zaikoBuy;
}

void ProcessingSqlData::changeToKg(
	std::vector<std::vector<std::string>>* thisYearZaiko,
	std::vector<std::vector<std::string>>* lastYearZaiko,
	std::vector<std::vector<std::string>>* buyMaterials
)
{
	ChangeToKg* toKg = new ChangeToKg;
	toKg->toKgByKanriTani(thisYearZaiko);
	toKg->toKgByKanriTani(lastYearZaiko);
	toKg->toKgByKobaiTani(buyMaterials);

	delete toKg;
}

void ProcessingSqlData::separate(
	std::vector<std::vector<std::string>>* thisYearZaiko,
	std::vector<std::vector<std::string>>* thisYearG,
	std::vector<std::vector<std::string>>* thisYearGt,
	std::vector<std::vector<std::string>>* lastYearZaiko,
	std::vector<std::vector<std::string>>* lastYearG,
	std::vector<std::vector<std::string>>* lastYearGt
)
{
	std::regex reG(R"(^G-.*$)");
	std::regex reGT(R"(^(GT-|GTS-).*$)");

	for (std::vector<std::string> line : *thisYearZaiko) {
		if (std::regex_match(line[0], reG)) {
			thisYearG->push_back(line);
		}
		if (std::regex_match(line[0], reGT)) {
			thisYearGt->push_back(line);
		}
	}
	for (std::vector<std::string> line : *lastYearZaiko) {
		if (std::regex_match(line[0], reG)) {
			lastYearG->push_back(line);
		}
		if (std::regex_match(line[0], reGT)) {
			lastYearGt->push_back(line);
		}
	}
}


void ProcessingSqlData::vecToMap(
	std::vector<std::vector<std::string>>* vec, 
	int keyCol,
	int valCol,
	std::map<std::string, float>* map
)
{
	for (std::vector<std::string> line : *vec) {
		if (map->count(line[keyCol]) == 0) {
			(*map)[line[keyCol]] = std::stof(line[valCol]);
			continue;
		}
		(*map)[line[keyCol]] += std::stof(line[valCol]);
	}
}


void ProcessingSqlData::gtMinusGt(
	std::map<std::string, float>* mapThisGt,
	std::map<std::string, float>* mapLastGt,
	std::map<std::string, float>* mapDiffGt
)
{
	for (std::string gt : *vecAllGt) {
		float thisQty = 0;
		float lastQty = 0;
		if (mapThisGt->count(gt) != 0) {
			thisQty = (*mapThisGt)[gt];
		}
		if (mapLastGt->count(gt) != 0) {
			lastQty = (*mapLastGt)[gt];
		}

		(*mapDiffGt)[gt] = lastQty - thisQty;
	}
}

void ProcessingSqlData::gtToG(std::map<std::string, float>* mapDiffGt, 
	                          std::map<std::string, float>* mapDiffG)
{
	GtComponent* gtCom = new GtComponent;
	gtCom->gtToG(mapDiffGt, mapDiffG);
	delete gtCom;
}

