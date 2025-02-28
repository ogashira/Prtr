#include "GetCsvZaikoThisYear.h"
#include "GetCsv.h"


GetCsvZaikoThisYear::GetCsvZaikoThisYear(std::string* path)
{
	this->path = path;
}

void GetCsvZaikoThisYear::ExecuteStatement(
	std::vector<std::vector<std::string>>* csvData
) 
{
	GetCsv getCsv = GetCsv();
	getCsv.getCsv(csvData, *path, ',');
	
}
