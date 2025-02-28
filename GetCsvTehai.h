#ifndef _GETCSVTEHAI_H_
#define _GETCSVTEHAI_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>


class GetCsvTehai: public IFSelectSql
{
public:
	GetCsvTehai(std::string* path);
	virtual ~GetCsvTehai() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	std::string* path;
};
#endif //_GETCSVTEHAI_H_
