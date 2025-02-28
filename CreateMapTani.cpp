#include "CreateMapTani.h"
#include "SelectHinban.h"
#include "SelectTehai.h"
#include "GetCsvHinban.h"
#include "GetCsvTehai.h"

void CreateMapTani::createMapKanriTani
(
	std::map<std::string, std::string>* mapKanriTani
) 
{
	std::vector<std::vector<std::string>> hinbanMaster;
	IFSelectSql* sHinban = new SelectHinban;
	//std::string path =
		//"./csvData/hinban.csv";
	//IFSelectSql* sHinban = new GetCsvHinban(&path);
	sHinban->ExecuteStatement(& hinbanMaster);

	for (std::vector<std::string> line : hinbanMaster) {
		(*mapKanriTani)[line[0]] = line[1];
	}
	
	delete sHinban;
}
void CreateMapTani::createMapKobaiTani
(
	std::map<std::string, std::vector<std::string>>* mapKobaiTani
)
{
	std::vector<std::vector<std::string>> tehaiMaster;
	IFSelectSql* sTehai = new SelectTehai;
	//std::string path =
		//"./csvData/tehai.csv";
	//IFSelectSql* sTehai = new GetCsvTehai(&path);
	sTehai->ExecuteStatement(&tehaiMaster);

	for (std::vector<std::string> line : tehaiMaster) {
		std::vector<std::string>* tmpVec = new std::vector<std::string>;
		tmpVec->push_back(line[1]);
		tmpVec->push_back(line[2]);
		tmpVec->push_back(line[3]);
		(*mapKobaiTani)[line[0]] = *tmpVec;
		delete tmpVec;
	}
	delete sTehai;
}
