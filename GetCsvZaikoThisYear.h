#ifndef _GETCSVZAIKOTHISYEAR_H_
#define _GETCSVZAIKOTHISYEAR_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>


class GetCsvZaikoThisYear: public IFSelectSql
{
public:
	GetCsvZaikoThisYear(std::string* path);
	virtual ~GetCsvZaikoThisYear() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	std::string* path;
};
#endif //_GETCSVZAIKOTHISYEAR_H_
