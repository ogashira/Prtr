#ifndef _IFSELECTSQL_H_
#define _IFSELECTSQL_H_

#include <string>
#include <vector>

class IFSelectSql
{

public:
	virtual void ExecuteStatement(std::vector<std::vector<std::string>>*) = 0;
};

#endif //_IFSELECTSQL_H_

