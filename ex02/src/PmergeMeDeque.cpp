#include "PmergeMe.hpp"

/* --------------------------------------------------- DEQUE -------------------------------------------------------- */

bool PmergeMe::middleCompareDeque(std::deque<std::deque<int> > &mainChain, int number, int left, int right, int &middle)
{
	middle = left + (right - left) / 2;
	return number > mainChain[middle][0];
}

void PmergeMe::insertPendDeque(size_t position, std::deque<std::deque<int> > &mainChain, std::deque<int> pendValue, size_t flagPos)
{
	std::deque<std::deque<int> >::iterator it = mainChain.begin();
	if (position + flagPos == mainChain.size())
		mainChain.push_back(pendValue);
	else if (position + flagPos == (size_t)-1)
		mainChain.push_front(pendValue);
	else
	{
		if (flagPos == 1)
			position++;
		std::advance(it, position);
		mainChain.insert(it, pendValue);
	}
}

void PmergeMe::binaryInsertionDeque(std::deque<std::deque<int> > pend, std::deque<std::deque<int> > &mainChain)
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

	// Inserisci dal più grande al più piccolo
	for (std::vector<size_t>::reverse_iterator it = insertionOrder.rbegin(); it != insertionOrder.rend(); ++it)
	{
		size_t index = *it;
		int left = 0;
		int right = mainChain.size() - 1;
		int middle = 0;

		while (left <= right)
		{
			if (middleCompareDeque(mainChain, pend[index][0], left, right, middle))
				left = middle + 1;
			else
				right = middle - 1;
		}

		if (left >= static_cast<int>(mainChain.size()))
			insertPendDeque(mainChain.size(), mainChain, pend[index], 1);
		else if (pend[index][0] > mainChain[left][0])
			insertPendDeque(left, mainChain, pend[index], 1);
		else
			insertPendDeque(left, mainChain, pend[index], -1);
	}
}

void PmergeMe::mergeDeque(std::deque<std::deque<int> > &inputChain)
{
	if (inputChain.size() <= 1)
		return;

	std::deque<std::deque<int> > mainChain;
	std::deque<std::deque<int> > pend;

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

	mergeDeque(mainChain);
	binaryInsertionDeque(pend, mainChain);

	inputChain = mainChain;
}


void PmergeMe::sortDeque()
{
	std::deque<std::deque<int> > firstChain;
	for (size_t i = 0; i < _numbers.size(); i++)
	{
		std::deque<int> tmp(1, _numbers[i]);
		firstChain.push_back(tmp);
	}

	clock_t start = clock();

	// generateJacobsthalNumbers(_numbers.size());
	mergeDeque(firstChain);

	clock_t end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;

	std::cout << "before: ";
	for (size_t i = 0; i < _numbers.size(); i++)
	{
		std::cout << _numbers[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "after: ";
	for (std::deque<std::deque<int> >::iterator it = firstChain.begin(); it != firstChain.end(); ++it)
	{
		std::cout << (*it)[0] << " ";
	}
	std::cout << std::endl;

	std::cout << "Time to process " << _howManyNumbers << " elements with std::deque : " << time << " seconds" << std::endl;
}
