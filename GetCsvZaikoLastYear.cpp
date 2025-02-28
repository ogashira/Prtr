#include "GetCsvZaikoLastYear.h"
#include "GetCsv.h"


GetCsvZaikoLastYear::GetCsvZaikoLastYear(std::string* path)
{
	this->path = path;
}

void GetCsvZaikoLastYear::ExecuteStatement(
	std::vector<std::vector<std::string>>* csvData
) 
{
	GetCsv getCsv;
	getCsv.getCsv(csvData, *path, ',');
	
}
