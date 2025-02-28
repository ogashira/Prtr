#ifndef _SELECTHATTYU_H_
#define _SELECTHATTYU_H_


#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"

class SelectPs : public IFSelectSql
{
public:
	SelectPs() {};
	virtual ~SelectPs () {};
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
};


#endif // _SELECTHATTYU_H_
