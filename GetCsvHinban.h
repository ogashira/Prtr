#ifndef _GETCSVHINBAN_H_
#define _GETCSVHINBAN_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>

class GetCsvHinban: public IFSelectSql
{
public:
	GetCsvHinban(std::string* path);
	virtual ~GetCsvHinban() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	std::string* path;
};
#endif //_GETCSVHINBAN_H_

