/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:39:23 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/14 14:11:36 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>

class RPN {
private:
	RPN();
	~RPN();
	RPN(const RPN& copy);
	RPN& operator=(const RPN& other);
	static bool _isOperator(char c);
	static void _handleOperator(std::stack<int>& stack, char val);
	static std::string _OPS_STR;

public:
	static void calcAndPrint(const std::string& expr);

	class RPNException : public std::exception {
		private:
			std::string _message;
		public:
			RPNException(const std::string& message);
			virtual ~RPNException() throw();
			virtual const char* what() const throw();
	};
};

#endif