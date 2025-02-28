#ifndef _TEST_H_
#define _TEST_H_

#include "IFSelectSql.h"
#include "SelectPs.h"
#include "SelectHinban.h"
#include "Printer.h"
#include "CalcDateSingleton.h"
#include <vector>

class Test
{
public:
	Test(CalcDateSingleton* myDate);
	virtual ~Test();
	int start();
	int start2();
	int start3();
private:
	CalcDateSingleton* myDate;
};

#endif //_TEST_H_
