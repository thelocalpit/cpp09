#pragma once

#include <map>
#include <list>
#include <iostream>

class CryptoExchange
{
private:
	std::string inputFileName;
	std::string historicalDataFileName;
	std::map<std::string, float> historicalDataMap;
	std::list<std::string> exchangeValues;
	std::list<std::string> exchangeDates;

	bool isLeapYear(int year) const;
	bool validateDate(const std::string &date) const;
	char findSeparator(const std::string &line) const;
	void parseHistoricalDataLine(const std::string &line, char separator);
	void parseExchangeLine(const std::string &line, const std::string &separator);

public:
	CryptoExchange();
	CryptoExchange(const CryptoExchange &copy);
	~CryptoExchange();
	CryptoExchange &operator=(const CryptoExchange &copy);

	std::map<std::string, float> getHistoricalData() const;
	std::list<std::string> getExchangeDates() const;
	std::list<std::string> getExchangeValues() const;
	std::string getInputFileName() const;
	std::string getHistoricalDataFileName() const;

	void loadCsvFile(const std::string &file);
	void loadExchangeFile(const std::string &file);
	void displayExchangeResults() const;

public:
	class DataError : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};
