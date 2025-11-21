
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:12:17 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/17 13:11:22 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <algorithm>
#include <deque>


/**
 * @brief puts str into val.
 * str must be of type T, otherwise returns EXIT_FAILURE.
 * @example "42" -> true, "42abc" -> false
 */
template <typename T>
void ftStrToT(T& val, std::string& str) {
	std::istringstream iss(str);
	iss >> val;
	if (iss.fail() || !iss.eof())
		throw std::invalid_argument("Error: " + str + " conversion failed");
}

std::vector<long> parseArgv(char **av) {

	std::vector<long> vec;
	long val;
	std::string str;

	for (size_t i = 0; av[i]; ++i) {
		str = av[i];
		if (str.size() && !isdigit(str.at(0)))
			throw std::invalid_argument("Error: positive number required: " + str);
		ftStrToT<long>(val, str);
		if (std::find(vec.begin(), vec.end(), val) != vec.end())
			throw std::invalid_argument("Error: invalid argument: " + str + " can't be added twice");
		vec.push_back(val);
	}
	return (vec);
}


int main(int ac, char **av) {

	if (ac < 2) {
		std::cout << "Usage: ./PmergeMe 1 2 3" << std::endl;
		return (EXIT_FAILURE);
	}

	std::vector<long> args;
	try {
		args = parseArgv(av + 1);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	try {
		std::vector<long> vecArgs(args.begin(), args.end());
		std::deque<long> deqArgs(args.begin(), args.end());

		PmergeMe< std::vector<long> >::printContainer("Before:\t", vecArgs, -1, "");

		double elapsedTimeVec = PmergeMe< std::vector<long> >::FJASort(vecArgs);
		double elapsedTimeDeq = PmergeMe< std::deque<long> >::FJASort(deqArgs);

		PmergeMe< std::vector<long> >::printContainer("After:\t", vecArgs, -1, "");

		std::cout << "Time to process a range of " << args.size() << " elements with std::vector: " << elapsedTimeVec << " us" << std::endl;
		std::cout << "Time to process a range of " << args.size() << " elements with std::deque: " << elapsedTimeDeq << " us" << std::endl;

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}