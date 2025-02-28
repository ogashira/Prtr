#ifndef _SELECTHINBAN_H_
#define _SELECTHINBAN_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>
#include "ConnectSql.h"


class SelectHinban : public IFSelectSql
{
public:
	SelectHinban() {};
	virtual ~SelectHinban() {};
	void ExecuteStatement(std::vector<std::vector<std::string>>*);
};
#endif // _SELECTHINBAN_H_

