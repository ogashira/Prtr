#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <string>
#include <map>
#include <vector>

class Control
{
public:
	int start();
private:
	std::map<std::string, float> mapMaterialQty;
	std::vector<std::vector<std::string>> prtrData;

};

#endif //_CONTROL_H_

