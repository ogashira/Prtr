#ifndef _CHANGETOKG_H_
#define _CHANGETOKG_H_

#include <string>
#include <map>
#include <vector>

class ChangeToKg
{
private:
	std::map<std::string, std::string>* mapKanriTani;
	std::map<std::string, std::vector<std::string>>* mapKobaiTani;
public:
	ChangeToKg();
	virtual ~ChangeToKg();

	void toKgByKanriTani(
		std::vector<std::vector<std::string>>* zaiko
	);
	void toKgByKobaiTani(
		std::vector<std::vector<std::string>>* zaiko
	);


};
#endif _CHANGETOKG_H_

