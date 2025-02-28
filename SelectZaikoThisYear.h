#ifndef _SELECTZAIKOTHISYEAR_H_
#define _SELECTZAIKOTHISYEAR_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"
#include "CalcDateSingleton.h"


class SelectZaikoThisYear : public IFSelectSql
{
public:
	SelectZaikoThisYear( CalcDateSingleton* myDate );
	virtual ~SelectZaikoThisYear() {};
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
private:
	CalcDateSingleton* myDate;
};

#endif //_SELECTZAIKOTHISYEAR_H_

