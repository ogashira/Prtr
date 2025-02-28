#ifndef _GETCSVBUYMATERIAL_H_
#define _GETCSVBUYMATERIAL_H_

#include "IFSelectSql.h"
#include <vector>
#include <string>


class GetCsvBuyMaterial : public IFSelectSql
{
public:
	GetCsvBuyMaterial(std::string* path);
	virtual ~GetCsvBuyMaterial() {};
	void ExecuteStatement
	(
		std::vector<std::vector<std::string>>* master
	);
private:
	std::string* path;
};
#endif //_GETCSVBUYMATERIAL_H_

