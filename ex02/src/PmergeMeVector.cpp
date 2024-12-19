#include "PmergeMe.hpp"

bool PmergeMe::middleCompareVector(std::vector<std::vector<int> > &mainChain, int number, int left, int right, int &middle)
{
	middle = left + (right - left) / 2;
	return number > mainChain[middle][0];
}

void PmergeMe::insertPendVector(size_t position, std::vector<std::vector<int> > &mainChain, std::vector<int> pendValue, size_t flagPos)
{
	std::vector<std::vector<int> >::iterator it = mainChain.begin();
	if (position + flagPos == mainChain.size())
		mainChain.push_back(pendValue);
	else if (position + flagPos == (size_t)-1)
		mainChain.insert(mainChain.begin(), pendValue);
	else
	{
		if (flagPos == 1)
			position++;
		std::advance(it, position);
		mainChain.insert(it, pendValue);
	}
}

void PmergeMe::binaryInsertionVector(std::vector<std::vector<int> > pend, std::vector<std::vector<int> > &mainChain)
{
	// generateJacobsthalNumbers(pend.size());
	std::vector<size_t> insertionOrder = getInsertionOrder(pend.size());

	// // Stampa l'ordine di inserimento
	// std::cout << "Insertion Order: ";
	// for (std::vector<size_t>::const_iterator it = insertionOrder.begin(); it != insertionOrder.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;


	for (std::vector<size_t>::reverse_iterator it = insertionOrder.rbegin(); it != insertionOrder.rend(); ++it)
	{
		size_t index = *it;
		int left = 0;
		int right = mainChain.size() - 1;
		int middle = 0;

		while (left <= right)
		{
			if (middleCompareVector(mainChain, pend[index][0], left, right, middle))
				left = middle + 1;
			else
				right = middle - 1;
		}

		if (left >= static_cast<int>(mainChain.size()))
			insertPendVector(mainChain.size(), mainChain, pend[index], 1);
		else if (pend[index][0] > mainChain[left][0])
			insertPendVector(left, mainChain, pend[index], 1);
		else
			insertPendVector(left, mainChain, pend[index], -1);
	}
}

void PmergeMe::mergeVector(std::vector<std::vector<int> > &inputChain)
{
	if (inputChain.size() <= 1)
		return;

	std::vector<std::vector<int> > mainChain;
	std::vector<std::vector<int> > pend;

	for (size_t i = 0; i < inputChain.size(); i += 2)
	{
		if (i + 1 < inputChain.size())
		{
			if (inputChain[i][0] > inputChain[i + 1][0])
			{
				mainChain.push_back(inputChain[i]);
				pend.push_back(inputChain[i + 1]);
			}
			else
			{
				mainChain.push_back(inputChain[i + 1]);
				pend.push_back(inputChain[i]);
			}
		}
		else
		{
			mainChain.push_back(inputChain[i]);
		}
	}

	mergeVector(mainChain);
	binaryInsertionVector(pend, mainChain);

	inputChain = mainChain;
}

void PmergeMe::sortVector()
{
	std::vector<std::vector<int> > firstChain;
	for (size_t i = 0; i < _numbers.size(); i++)
	{
		std::vector<int> tmp(1, _numbers[i]);
		firstChain.push_back(tmp);
	}

	clock_t start = clock();

	// generateJacobsthalNumbers(_numbers.size());
	mergeVector(firstChain);

	clock_t end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;

	std::cout << "before: ";
	for (size_t i = 0; i < _numbers.size(); i++)
	{
		std::cout << _numbers[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "after: ";
	for (std::vector<std::vector<int> >::iterator it = firstChain.begin(); it != firstChain.end(); ++it)
	{
		std::cout << (*it)[0] << " ";
	}
	std::cout << std::endl;

	std::cout << "Time to process " << _howManyNumbers << " std::Vector: " << time << " seconds" << std::endl;
}