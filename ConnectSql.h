#ifndef _CONNECTSQL_H_
#define _CONNECTSQL_H_

#include <Windows.h>
#include <sqlext.h>
#include <cstdio>
#include <string>


class ConnectSql {

public:
	SQLHSTMT connectSql(std::string);


};


#endif // _CONNECTSQL_H_
