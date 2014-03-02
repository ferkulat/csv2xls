/*** testMain.cpp ***/
#include "filenameTestMain.h"
#include <CppUTest/CommandLineTestRunner.h>

int main(	int argc,
			char* argv[])
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
