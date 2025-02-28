#ifndef _SELECTZAIKOLASTYEAR_H_
#define _SELECTZAIKOLASTYEAR_H_


#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"
#include "CalcDateSingleton.h"


class SelectZaikoLastYear : public IFSelectSql
{
public:
	SelectZaikoLastYear( CalcDateSingleton* myDate );
	virtual ~SelectZaikoLastYear() {};
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
private:
	CalcDateSingleton* myDate;
};
#endif // _SELECTZAIKOLASTYEAR_H_

