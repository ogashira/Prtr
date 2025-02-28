#ifndef _CREATEMAPTANI_H_
#define _CREATEMAPTANI_H_

#include <map>
#include <vector>
#include <string>

class CreateMapTani
{
public:
	void createMapKanriTani
	(
		std::map<std::string, std::string> * mapKanriTani
	);
	void createMapKobaiTani
	(
		std::map<std::string, std::vector<std::string>>* mapKobaiTani
	);
};

#endif //_CREATEMAPTANI_H_

