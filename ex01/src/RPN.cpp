#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& copy)
{
	*this = copy;
}

RPN::~RPN()
{
}

RPN&	RPN::operator=(const RPN& copy)
{
	if (this == &copy)
		return *this;
	return *this;
}

void	RPN::RpnCalculation(std::string math)
{
	int nbr;
	int nbr_02;

	for (std::string::iterator it = math.begin(); it != math.end(); it++)
	{
		if (std::isdigit(*it))
		{
			if (*it >= '0' && *it <= '9')
			{
				stack.push(*it - '0'); // Converti il carattere in numero
			}
			else
			{
				std::cout << "Error: numbers must be less than 10" << std::endl;
				return;
			}
		}
		else if (*it == '+' || *it == '/' || *it == '*' || *it == '-')
		{
			if (stack.size() < 2)
			{
				std::cout << "Error: not enough operands in the stack" << std::endl;
				return;
			}
			nbr_02 = stack.top();
			stack.pop();
			nbr = stack.top();
			stack.pop();

			if (*it == '+')
			{
				stack.push(nbr + nbr_02);
			}
			else if (*it == '-')
			{
				stack.push(nbr - nbr_02);
			}
			else if (*it == '/')
			{
				if (nbr_02 == 0)
				{
					std::cout << "Error: division by zero" << std::endl;
					return;
				}
				stack.push(nbr / nbr_02);
			}
			else if (*it == '*')
			{
				stack.push(nbr * nbr_02);
			}
		}
		else if (!std::isspace(*it))
		{
			std::cout << "Error: invalid character '" << *it << "'" << std::endl;
			return;
		}
	}
	std::cout << stack.top() << std::endl;
}
