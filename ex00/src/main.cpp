/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:13:30 by miloniemaz        #+#    #+#             */
/*   Updated: 2025/11/24 13:11:37 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>


int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./btc inputfile" << std::endl;
		return (EXIT_FAILURE);
	}
	char *inputFileName = av[1];
	BitcoinExchange be;

	if (be.parseFile(DBFILENAME, DB) == EXIT_FAILURE) {
		return (EXIT_FAILURE);
	}

	if (be.parseFile(inputFileName, INPUT) == EXIT_FAILURE) {
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
