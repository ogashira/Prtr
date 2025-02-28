#ifndef _CREATEPRTRDATA_H_
#define _CREATEPRTRDATA_H_

#include<string>
#include<vector>
#include<map>
#include "GetCsv.h"

class CreatePrtrData
{
private:
	std::vector<std::vector<std::string>>* prtrData;
	std::map<std::string, float>* mapMaterialQty;
	std::map<std::string, float>* mapPrtrQty;
	std::map<std::string, float>* mapPrtrEmissionFactor;
public:
	CreatePrtrData(
		std::vector<std::vector<std::string>>* prtrData,
		std::map<std::string, float>* mapMaterialQty
	);
	~CreatePrtrData();
	void createPrtrData();

private:
	void createMapPrtrQty(GetCsv* getCsv);
	void createMapPrtrEmissionFactor(GetCsv* getCsv);
};

#endif //_CREATEPRTRDATA_H_

