#include <stdio.h>
#include "FooConfig.hpp"

#include "foo/foo.h"	//external
#include <bar/bar.h>	//another libray
#include <foo.h> 		//internal


// Accessing the FooConfig
void foo::help(std::string argv)
{
	fprintf(stdout,"%s Version %d.%d\n",
	argv.c_str(),
	Foo_VERSION_MAJOR,
	Foo_VERSION_MINOR);
	fprintf(stdout,"Usage: %s number\n",argv.c_str());
}

// Using internal functions and also Boost
double foo::mysqrt(const int &inputValue)
{
	boost::any val = inputValue;

	if(isValueAllowed(inputValue) && foo::is_int(val))
    {
		return sqrt(inputValue);
	}

	return 1.0;
}

// Just using another package
double foo::mylog(const int &inputValue)
{
	return bar::mylog(inputValue);
}

bool foo::is_int(const boost::any & operand)
{
    return operand.type() == typeid(int);
}

