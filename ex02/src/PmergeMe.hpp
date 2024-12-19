#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <set>
#include <ctime>

class PmergeMe
{
private:
	std::vector<int> _numbers;
	std::vector<int> _jacobsthal;
	int _howManyNumbers;

public:
	PmergeMe();
	PmergeMe(const PmergeMe &toCopy);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &toCopy);
	std::vector<int> getNumbers() const;
	std::vector<int> getJacobsthal() const;

	void checkArguments(char **argv);
	void loadNumbers(char **argv);
	void generateJacobsthalNumbers(size_t n);
	std::vector<size_t> getInsertionOrder(size_t size);

	void sortDeque();
	void binaryInsertionDeque(std::deque<std::deque<int> > pend, std::deque<std::deque<int> > &ordered);
	void insertPendDeque(size_t position, std::deque<std::deque<int> > &ordered, std::deque<int> pendValue, size_t flagPos);
	bool middleCompareDeque(std::deque<std::deque<int> > &ordered, int number, int start, int end, int &middle);
	void mergeDeque(std::deque<std::deque<int> > &inputChain);


	void sortVector();
	void binaryInsertionVector(std::vector<std::vector<int> > pend, std::vector<std::vector<int> > &ordered);
	bool middleCompareVector(std::vector<std::vector<int> > &ordered, int number, int left, int right, int &middle);
	void mergeVector(std::vector<std::vector<int> > &inputChain);
	void insertPendVector(size_t position, std::vector<std::vector<int> > &ordered, std::vector<int> pendValue, size_t flagPos);
	// std::vector<size_t> getInsertionOrderVector(size_t size);



public:
	class NegativeNumber : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class NotAnInteger : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class HasDuplicated : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

