#include "GetCsvHinban.h"
#include "GetCsv.h"


GetCsvHinban::GetCsvHinban(std::string* path)
{
	this->path = path;
}

void GetCsvHinban::ExecuteStatement(
	std::vector<std::vector<std::string>>* csvData
) 
{
	GetCsv getCsv;
	getCsv.getCsv(csvData, *path, ',');
	
}
