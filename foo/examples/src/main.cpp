#include <stdlib.h>
#include <stdio.h>
#include <foo/foo.h>

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		std::string name = argv[0];
		foo::help(name);
		return 1;
	}
	
	double inputValue = atof(argv[1]);
	double outputValue = foo::mysqrt(inputValue);
	fprintf(stdout,"sqrt: The square root of %g is %g\n",
	inputValue, outputValue);

	return 0;
}