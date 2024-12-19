#include "CryptoExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

CryptoExchange::CryptoExchange() : inputFileName(""), historicalDataFileName("") {}

CryptoExchange::CryptoExchange(const CryptoExchange &copy)
{
	*this = copy;
}

CryptoExchange::~CryptoExchange() {}

CryptoExchange &CryptoExchange::operator=(const CryptoExchange &copy)
{
	if (this == &copy)
		return *this;
	this->historicalDataFileName = copy.getHistoricalDataFileName();
	this->inputFileName = copy.getInputFileName();
	this->historicalDataMap = copy.getHistoricalData();
	this->exchangeDates = copy.getExchangeDates();
	this->exchangeValues = copy.getExchangeValues();
	return *this;
}

std::map<std::string, float> CryptoExchange::getHistoricalData() const
{
	return this->historicalDataMap;
}

std::list<std::string> CryptoExchange::getExchangeDates() const
{
	return exchangeDates;
}

std::list<std::string> CryptoExchange::getExchangeValues() const
{
	return exchangeValues;
}

std::string CryptoExchange::getInputFileName() const
{
	return this->inputFileName;
}

std::string CryptoExchange::getHistoricalDataFileName() const
{
	return this->historicalDataFileName;
}

void CryptoExchange::parseHistoricalDataLine(const std::string &line, char separator)
{
	unsigned int separatorPos = line.find(separator);
	std::string date = line.substr(0, separatorPos);
	std::string valueStr = line.substr(separatorPos + 1);
	float value;
	std::istringstream(valueStr) >> value;
	historicalDataMap[date] = value;
}

void CryptoExchange::parseExchangeLine(const std::string &line, const std::string &separator)
{
	if (line.find(separator) == std::string::npos)
	{
		exchangeDates.push_back(line);
		exchangeValues.push_back("");
	}
	else
	{
		exchangeDates.push_back(line.substr(0, line.find(separator)));
		exchangeValues.push_back(line.substr(line.find(separator) + separator.length()));
	}
}

void CryptoExchange::loadCsvFile(const std::string &file)
{
	if (file.substr(file.size() - 4) != ".csv")
		throw CryptoExchange::DataError();

	std::ifstream inFile(file.c_str());
	if (!inFile.is_open())
		throw CryptoExchange::DataError();

	historicalDataFileName = file;
	std::string line;
	getline(inFile, line);
	char separator = ',';

	while (getline(inFile, line))
	{
		parseHistoricalDataLine(line, separator);
	}
}

void CryptoExchange::loadExchangeFile(const std::string &file)
{
	std::ifstream inFile(file.c_str());
	if (!inFile.is_open())
		throw CryptoExchange::DataError();

	if (!inputFileName.empty())
	{
		exchangeDates.clear();
		exchangeValues.clear();
	}

	inputFileName = file;
	std::string line;
	getline(inFile, line);

	if (line.find(" | ") == std::string::npos)
		throw CryptoExchange::DataError();

	std::string separator = " | ";

	while (getline(inFile, line))
	{
		parseExchangeLine(line, separator);
	}
}

bool CryptoExchange::isLeapYear(int year) const
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool CryptoExchange::validateDate(const std::string &date) const
{
	std::istringstream dateStream(date.c_str());
	int year, month, day;
	char dash1, dash2;

	if (!(dateStream >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31 || dash1 != '-' || dash2 != '-')
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2)
	{
		if (isLeapYear(year) && day > 29)
			return false;
		if (!isLeapYear(year) && day > 28)
			return false;
	}
	return true;
}

void CryptoExchange::displayExchangeResults() const
{
	if (inputFileName.empty() || historicalDataFileName.empty())
		throw CryptoExchange::DataError();

	std::list<std::string>::const_iterator it_values = exchangeValues.begin();
	std::list<std::string>::const_iterator it_dates = exchangeDates.begin();

	while (it_dates != exchangeDates.end())
	{
		if (it_values->empty())
		{
			std::cout << "Error: bad input => " << *it_dates << std::endl;
		}
		else if (!validateDate(*it_dates))
		{
			std::cout << "Error: bad input => " << *it_dates << std::endl;
		}
		else
		{
			try
			{
				float number;
				std::istringstream(*it_values) >> number;
				if (number < 0 || number > 1000)
					throw CryptoExchange::DataError();

				std::map<std::string, float>::const_iterator closest = historicalDataMap.lower_bound(*it_dates);

				if (closest == historicalDataMap.end() || (closest == historicalDataMap.begin() && closest->first != *it_dates))
				{
					std::cout << "Error: date not found in historical data => " << *it_dates << std::endl;
				}
				else
				{
					if (closest == historicalDataMap.end() || closest->first != *it_dates)
					{
						--closest;
					}
					float result = number * closest->second;
					std::cout << *it_dates << " => " << *it_values << " = " << result << std::endl;
				}
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		++it_values;
		++it_dates;
	}
}

const char *CryptoExchange::DataError::what() const throw()
{
	return "Data error";
}
