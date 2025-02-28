#ifndef _CREATEMATERIALQTY_H_
#define _CREATEMATERIALQTY_H_

#include "CalcDateSingleton.h"
#include <map>
#include <vector>

class CreateMaterialQty
{
private:
	std::map<std::string, float>* mapThisYearG;
	std::map<std::string, float>* mapLastYearG;
	std::map<std::string, float>* mapDiffG;
	std::map<std::string, float>* mapBuyG;
	std::vector<std::string>* vecAllG;
	CalcDateSingleton* myDate;
public:
	CreateMaterialQty( CalcDateSingleton* myDate);

	void createMaterialQty(std::map<std::string, float>* prtrData);

private:
	void calcMaterialQty(std::map<std::string, float>* prtrData);
};
#endif //_CREATEMATERIALQTY_H_

