#include "GetCsvTehai.h"
#include "GetCsv.h"


GetCsvTehai::GetCsvTehai(std::string* path)
{
	this->path = path;
}

void GetCsvTehai::ExecuteStatement(
	std::vector<std::vector<std::string>>* csvData
) 
{
	GetCsv gCsv; 
	gCsv.getCsv(csvData, *path, ',');
}
