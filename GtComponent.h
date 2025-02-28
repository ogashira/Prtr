#ifndef _GTCOMPONENT_H_
#define _GTCOMPONENT_H_

#include <vector>
#include <string>
#include <map>

class GtComponent
{
private:
	std::vector<std::vector<std::string>> gtComponent;
	std::vector<std::vector<std::string>> gtPsMaster;
	std::vector<std::vector<std::string>> hinbanMaster;
	std::map<std::string, std::string> mapTani;
	std::map<std::string, int> mapForExists; //int‚Í˜A”Ô

public:
	GtComponent();
	void gtToG(
		std::map<std::string, float>* mapDiffGt,
		std::map<std::string, float>* mapDiffG
	);

private:
	void createMapTani();
	void createGtComponent();
	void createMapForExists();
	void sortingTableProcess(
		std::vector<std::vector<std::string>>* table,
		std::vector<float>* ratioVec 
	);
	float toKg(std::string weight, std::string child);
};



#endif //_GTCOMPONENT_H_
