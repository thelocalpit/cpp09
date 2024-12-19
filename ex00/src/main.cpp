#include "CryptoExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "error: try launching the program with \"./bitcoinExchange + \"input.csv\"" << std::endl;
		return (1);
	}
	CryptoExchange bitcoin;


	try
	{
		bitcoin.loadCsvFile("./data.csv");
		bitcoin.loadExchangeFile((std::string)argv[1]);
		bitcoin.displayExchangeResults();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
