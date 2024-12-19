#pragma once

#include <iostream>
#include <stack>

class RPN
{
	private:
		std::stack<int> stack;
	public:
		RPN();
		RPN(const RPN& copy);
		~RPN();
		RPN&	operator=(const RPN& copy);
		void 	RpnCalculation(std::string math);
};

