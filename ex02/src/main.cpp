#include "PmergeMe.hpp"
#include <vector>
#include <list>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Error: \"program name\" + positive integers" << std::endl;
		return 1;
	}

	PmergeMe _PmergeMe;

	try
	{
		_PmergeMe.checkArguments(&argv[1]);
		_PmergeMe.loadNumbers(&argv[1]);
		_PmergeMe.generateJacobsthalNumbers(_PmergeMe.getNumbers().size());
		_PmergeMe.sortDeque();
		_PmergeMe.sortVector();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}


	return 0;
}
