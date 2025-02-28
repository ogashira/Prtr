#ifndef _SELECTBUYMATERIAL_H_
#define _SELECTBUYMATERIAL_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"
#include "CalcDateSingleton.h"

class SelectBuyMaterial : public IFSelectSql
{
public:
	SelectBuyMaterial(CalcDateSingleton* myDate);
	virtual ~SelectBuyMaterial() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	CalcDateSingleton* myDate;
};

#endif //_SELECTBUYMATERIAL_H_
