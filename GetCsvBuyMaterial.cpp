#include "GetCsvBuyMaterial.h"
#include "GetCsv.h"


GetCsvBuyMaterial::GetCsvBuyMaterial(std::string* path)
{
	this->path = path;
}

void GetCsvBuyMaterial::ExecuteStatement(
	std::vector<std::vector<std::string>>* csvData
) 
{
	GetCsv getCsv;
	getCsv.getCsv(csvData, *path, ',');
	
}
