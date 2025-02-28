#ifndef _GETCSVPS_H_
#define _GETCSVPS_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>


class GetCsvPs: public IFSelectSql
{
public:
	GetCsvPs(std::string* path);
	virtual ~GetCsvPs() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	std::string* path;
};
#endif //_GETCSVPS_H_
