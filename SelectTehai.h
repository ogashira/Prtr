#ifndef _SELECTTEHAI_H_
#define _SELECTTEHAI_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"

class SelectTehai : public IFSelectSql
{
public:
	SelectTehai() {};
	virtual ~SelectTehai() {};
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
};

#endif //_SELECTTEHAI_H_



