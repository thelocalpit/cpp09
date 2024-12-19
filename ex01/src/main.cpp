#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: usage: \"./RPN\" \"matematical expression in RPN\"" << std::endl;
		return 1;
	}

	RPN rpn;
	rpn.RpnCalculation(argv[1]);

	return 0;
}
