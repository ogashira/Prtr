#ifndef _GETCSVZAIKOLASTYEAR_H_
#define _GETCSVZAIKOLASTYEAR_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>


class GetCsvZaikoLastYear: public IFSelectSql
{
public:
	GetCsvZaikoLastYear(std::string* path);
	virtual ~GetCsvZaikoLastYear() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	std::string* path;
};
#endif //_GETCSVZAIKOLASTYEAR_H_
