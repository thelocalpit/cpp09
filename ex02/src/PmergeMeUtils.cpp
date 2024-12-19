#include "PmergeMe.hpp"

/* ------------------------- basics ------------------------------------- */

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}


PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	if (this == &copy)
		return *this;
	this->_numbers = copy.getNumbers();
	return *this;
}

PmergeMe::~PmergeMe() {}

/* ------------------------ exceptions ------------------------------------ */

const char *PmergeMe::NotAnInteger::what() const throw()
{
	return "Error:  not all integers";
}

const char *PmergeMe::NegativeNumber::what() const throw()
{
	return "Error: negative numbers";
}

const char *PmergeMe::HasDuplicated::what() const throw()
{
	return "Error: duplicated numbers";
}

std::vector<int> PmergeMe::getNumbers() const
{
	return _numbers;
}

/* -------------------------- checkArguments ------------------------------ */

void PmergeMe::checkArguments(char **argv)
{
	std::set<int> uniqueStrings;
	std::string str;
	int number;

	for (int i = 0; argv[i]; i++)
	{
		std::istringstream iss(argv[i]);
		if (!(iss >> number))
			throw PmergeMe::NotAnInteger();
		else if (number < 0)
			throw PmergeMe::NegativeNumber();
		// else if (!uniqueStrings.insert(number).second)
		// 	throw PmergeMe::HasDuplicated();
	}
}

void PmergeMe::loadNumbers(char **argv)
{
	std::string str;
	int number;
	_howManyNumbers = 0;

	for (int i = 0; argv[i]; i++)
	{
		std::istringstream iss(argv[i]);
		iss >> number;
		this->_numbers.push_back(number);
		_howManyNumbers++;
	}
}

/* ----------------  calcolo Jacobsthal ------------------------------------ */

void PmergeMe::generateJacobsthalNumbers(size_t n)
{
	_jacobsthal.clear();
	_jacobsthal.push_back(0);
	_jacobsthal.push_back(1);
	size_t j = 1;
	while (true)
	{
		size_t next = _jacobsthal[j] + 2 * _jacobsthal[j - 1];
		if (next >= n)
			break;
		_jacobsthal.push_back(next);
		++j;
	}
}

std::vector<size_t> PmergeMe::getInsertionOrder(size_t n)
{
	std::vector<size_t> order;
	std::vector<bool> inserted(n, false);

	// Aggiungi 0 come primo elemento
	order.push_back(0);
	inserted[0] = true;

	size_t i = 1;			 // Indice per i numeri di Jacobsthal
	size_t lastInserted = 0; // Ultimo numero inserito

	while (order.size() < n)
	{
		// Controlla se ci sono numeri di Jacobsthal validi da inserire
		while (i < _jacobsthal.size() && _jacobsthal[i] < static_cast<int>(n))
		{
			// Inserisci il numero di Jacobsthal
			if (!inserted[_jacobsthal[i]])
			{
				order.push_back(_jacobsthal[i]);
				inserted[_jacobsthal[i]] = true;
				lastInserted = _jacobsthal[i]; // Aggiorna l'ultimo numero inserito

				// Inserisci tutti i numeri minori fino all'ultimo inserito
				for (size_t k = lastInserted - 1; k > 0; --k)
				{
					if (!inserted[k])
					{
						order.push_back(k);
						inserted[k] = true;
					}
				}
			}
			++i; // Passa al numero di Jacobsthal successivo
		}

		// Inserisci il numero più vicino non ancora inserito
		for (size_t j = lastInserted + 1; j < n; ++j)
		{
			if (!inserted[j]) // Trova il primo numero non inserito
			{
				order.push_back(j);
				inserted[j] = true;
				lastInserted = j; // Aggiorna l'ultimo numero inserito
				break;			  // Esci dal ciclo dopo aver inserito
			}
		}
	}

	return order;
}

