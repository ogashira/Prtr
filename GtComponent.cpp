#include "GtComponent.h"
#include "SelectPs.h"
#include "IFSelectSql.h"
#include "SelectHinban.h"
#include "Printer.h"
#include "getCsvPs.h"
#include "getCsvHinban.h"
#include <iostream>
#include <regex>

GtComponent::GtComponent() 
{
	IFSelectSql* ps = new SelectPs;
	//std::string path; 
	//path =
		//"./csvData/ps.csv";
	//IFSelectSql* ps = new GetCsvPs(&path);
	ps->ExecuteStatement(&gtPsMaster);

	IFSelectSql* hinban = new SelectHinban;
	//path =
		//"./csvData/hinban.csv";
	//IFSelectSql* hinban = new GetCsvHinban(&path);
	hinban->ExecuteStatement(&hinbanMaster);

	delete ps;
	delete hinban;

	//hinbanMasterからmapTaniをつくる 品番と単位のmap
	createMapTani();
	//gtMsMasterからmapForExistsを作る　親品番と連番のmap
	createMapForExists();

	createGtComponent();

}

void GtComponent::gtToG(
					std::map<std::string, float>* mapDiffGt,
					std::map<std::string, float>* mapDiffG )
//ProcessingSqlDataからmapを受け取って、mapDiffGt->mapDiffGを作る
{
	for (auto iter = mapDiffGt->begin(); iter != mapDiffGt->end(); iter++) {
		if (iter->second == 0) {
			continue;
		}
		for (std::vector<std::string> line : gtComponent) {
			if (iter->first == line[0]) {
				if (mapDiffG->count(line[1]) == 0) {
					(*mapDiffG)[line[1]] = std::stof(line[2]) * iter->second;
				}
				else {
					(*mapDiffG)[line[1]] = (*mapDiffG)[line[1]] 
						                 + std::stof(line[2]) * iter->second;
				}
			}
		}

	}

}

void GtComponent::createMapTani() {
	for (std::vector<std::string> line : hinbanMaster){
		mapTani[line[0]] = line[1];
	}
}

void GtComponent::createMapForExists()
{
	int cnt = 0;
	for (std::vector<std::string> line : gtPsMaster) {
		//存在する場合は1を返し、存在しない場合は0を返す
		if (mapForExists.count(line[0]) == 0) {
			mapForExists[line[0]] = cnt;
			cnt++;
		}

	}
}

void GtComponent::createGtComponent() {
	
	std::regex re(R"(^(GT-|GTS-|S2-ST32|S2-UT210|S6-UVT|S8-KD).*$)");

	std::vector<std::vector<std::string>> sortingTable;
	std::vector<float> ratioVec;
	int psCnt = 0;
	while (psCnt < gtPsMaster.size()) {

		if (!std::regex_match(gtPsMaster[psCnt][0], re)) {
			psCnt++;
			continue;
		}

		std::string loopHinban = gtPsMaster[psCnt][0];
		int tableCnt = 0;
		while (loopHinban == gtPsMaster[psCnt][0]) {
			sortingTable.push_back(gtPsMaster[psCnt]);
			float wt = this->toKg(gtPsMaster[psCnt][2], gtPsMaster[psCnt][1]);
			ratioVec.push_back(wt);
			tableCnt++;
			if (psCnt == gtPsMaster.size() - 1) {
				psCnt++;
				break;
			}
			psCnt++;
		}
		sortingTableProcess(&sortingTable, &ratioVec);
		ratioVec.clear();
		sortingTable.clear();
	}
}

void GtComponent::sortingTableProcess( 
	std::vector<std::vector<std::string>>* table, 
	std::vector<float>* ratioVec ){

	float sum = 0;
	for (float f : *ratioVec) {
		sum += f;
	}

	for (int i = 0; i < ratioVec->size(); i++) {
		(*table)[i][2] = std::to_string((*ratioVec)[i] / sum);
	}

	//psマスタの親品番が存在しなければgtComponentに、
	//存在すれば、subTableに入れる
	std::vector<std::vector<std::string>> subTable;
	std::vector<std::vector<std::string>> subTable2;

	std::vector<float> wts;
	float total=0;
	while (!table->empty()) {
		for (int i = 0; i < table->size(); i++) {

			if (mapForExists.count((*table)[i][1]) == 0) {
				gtComponent.push_back((*table)[i]);
				continue;
			}

			//subTableとwtsに要素を入れる
			total = std::stof((*table)[i][2]);
			for (int j = 0; j < gtPsMaster.size(); j++) {
				if ((*table)[i][1] == gtPsMaster[j][0]) {
					subTable.push_back(gtPsMaster[j]);
					//wts.push_back(to_Kg(gtPsMaster[j][2]));
					//to_Kgを作って、floatを返す
					//wts.push_back(std::stof(gtPsMaster[j][2]));
					wts.push_back(this->toKg(gtPsMaster[j][2], gtPsMaster[j][1]));
				}
			}
			sum = 0;
			for (float wt : wts) {
				sum += wt;
			}
			//subTableのweightと親品番を変更する
			for (int k = 0; k < subTable.size(); k++) {
				subTable[k][2] = std::to_string((total / sum) * wts[k]); //20240909修正
				subTable[k][0] = (*table)[i][0];
			}
			//subtable２にsubTableをコピ
			for (std::vector<std::string> line : subTable) {
				subTable2.push_back(line);
			}
			subTable.clear();
		}
		table->clear();
		for (std::vector<std::string> line : subTable2) {
			table->push_back(line);
		}
		subTable2.clear();
	}
}


float GtComponent::toKg(std::string weight, std::string child)
{
	float wt = std::stof(weight);
	if (mapTani[child] == "G") {
		return wt / 1000;
	}
	return wt;
}


