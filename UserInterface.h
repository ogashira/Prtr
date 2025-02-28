#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

#include <vector>
#include <string>
#include "CalcDateSingleton.h"

class UserInterface
{
public:
	void startChat(CalcDateSingleton* myDate);
	std::string getMyYear();

private:
	std::string myYear;
};
#endif //_USERINTERFACE_H_

