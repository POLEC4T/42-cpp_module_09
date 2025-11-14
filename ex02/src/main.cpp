/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:12:17 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/14 16:02:10 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <vector>

/**
 * todo : optimize with memoization
 */
std::vector<unsigned long> getJacobsthalNums(size_t limitIter) {
	std::vector<unsigned long> nums;
	if (limitIter == 0)
		return (nums);
	nums.push_back(0);
	if (limitIter == 1)
		return (nums);
	nums.push_back(1);
	for (size_t i = 2; i < limitIter; i++)
		nums.push_back(nums[i - 1] + 2 * nums[i - 2]);
	return (nums);
}


#include <iostream>


int main(int ac, char **av) {

	if (ac != 2) {
		return (EXIT_FAILURE);
	}
	std::vector<unsigned long> jacobsthal = getJacobsthalNums(std::atoi(av[1]));
	for (size_t i = 0; i < jacobsthal.size(); i++)
		std::cout << jacobsthal[i] << " ";
	std::cout << std::endl;
	

	return (EXIT_SUCCESS);
}