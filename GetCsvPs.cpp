#include "GetCsvPs.h"
#include "GetCsv.h"


GetCsvPs::GetCsvPs(std::string* path)
{
	this->path = path;
}

void GetCsvPs::ExecuteStatement(
	std::vector<std::vector<std::string>>* csvData
) 
{
	GetCsv getCsv;
	getCsv.getCsv(csvData, *path, ',');
	
}
