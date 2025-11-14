/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:38:38 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/14 13:56:17 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>

int main (int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./RPN \"RPN expression\"" << std::endl;
		return (EXIT_FAILURE);
	}

	try {
		RPN::calcAndPrint(av[1]);
	} catch (const RPN::RPNException& e) {
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}