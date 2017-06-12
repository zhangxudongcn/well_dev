#include "stdafx.h"
#include "lcapplication.h"
#include "cwp.h"
int main(int argc, char *argv[])
{
	LCApplication a(argc, argv);
	return a.exec();
}
