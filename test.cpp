#include <iostream>
#include <vector>
using namespace std;
#include <stdio.h>
#include <unistd.h>

#include "CException.h"
#include<typeinfo>
#include <sstream>
int main( )
{
	using namespace Taiji;
	try
	{
		throw MysqlConnErr("sfsf");
	} catch( CException &e )
	{
		cout << e.what() << endl;
		cout <<e.getErrorCode() << endl;
		cout<<e.getErrInfo()<<endl;
	}

	return 1;
}
