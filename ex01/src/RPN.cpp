/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:29:48 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/14 14:18:48 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

std::string RPN::_OPS_STR("+-/*");

RPN::RPN() {
}

RPN::~RPN() {}

RPN::RPN(const RPN& copy) {
	(void)copy;
}

RPN& RPN::operator=(const RPN& other) {
	(void)other;
	return (*this);
}

bool RPN::_isOperator(char c) {
	return (RPN::_OPS_STR.find(c) != std::string::npos);
}

void RPN::_handleOperator(std::stack<int>& stack, char op){
	if (stack.size() < 2)
		throw RPNException("Error: not enough digits");
	
	int topdigit = stack.top();
	stack.pop();
	int secondtopdigit = stack.top();
	stack.pop();

	switch (op) {
		case ('*'):
			stack.push(secondtopdigit * topdigit);
			break;
		case ('/'):
			if (topdigit == 0)
				throw RPNException("Error: division by zero");
			stack.push(secondtopdigit / topdigit);
			break;
		case ('+'):
			stack.push(secondtopdigit + topdigit);
			break;
		case ('-'):
			stack.push(secondtopdigit - topdigit);
		default:
			break;
	}
}

void RPN::calcAndPrint(const std::string& expr) {
	std::istringstream iss(expr);
	std::stack<int> stack;
	char val;
	int nextsep;
	int nextval;
	if (std::iswspace(iss.peek()))
		throw RPNException("Error: expected no leading space");

	while (iss >> val) {
		nextsep = iss.get();
		nextval = iss.peek();
		if (nextsep != -1 && nextsep != ' ')
			throw RPNException("Error: expected a space between each element");
		if (nextval != -1 && std::iswspace(nextval))
			throw RPNException("Error: expected only one space between each element");
		if (nextval == -1 && std::iswspace(nextsep))
			throw RPNException("Error: expected no final space");

		if (std::isdigit(val))
			stack.push(val - 48);
		else if (_isOperator(val))
			_handleOperator(stack, val);
		else
			throw RPNException("Error: unhandled character found");
	}

	if (stack.size() > 1)
		throw RPNException("Error: too many digits");
	else if (stack.empty())
		throw RPNException("Error: no input");
	std::cout << stack.top() << std::endl;
}


RPN::RPNException::RPNException(const std::string& message) {
	_message = message;
}

RPN::RPNException::~RPNException() throw() {}

const char* RPN::RPNException::what() const throw() {
	return (_message.c_str());
}