/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:12:10 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/21 17:48:49 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <vector>
# include <cstdlib>
# include <string>

# define PRINT_LOGS 0
# define NB_PRINT_NUMS 30

template <typename Container>
class PmergeMe {
private:
	PmergeMe();
	PmergeMe(const PmergeMe<Container>& copy);
	PmergeMe& operator=(const PmergeMe<Container>& other);
	~PmergeMe();
	static void 							_swapItValues(typename Container::iterator it1, typename Container::iterator it2);
	static void 							_reverseContPart(typename Container::iterator& it, typename Container::iterator& ite);
	static Container						_getJacobsthalOrder(long size);
	static void								_setMainAndPending(Container& cont, Container& main, Container& pending);
	static void								_fillMainInOrder(Container& main, Container& pending, typename Container::value_type& _lastSingleNum);
	static typename Container::iterator		_binarySearch(typename Container::iterator first, typename Container::iterator last, const long& val);
	static void								_insertValSorted(Container& main, long val, typename Container::iterator startrange, typename Container::iterator endrange);
	static Container						_processSort(Container cont);
	
public:
	static void								printContainer(const std::string& name, const Container& cont, long toColor, const std::string& color);
	static double							FJASort(Container& args);
};

# include "PmergeMe.tpp"

#endif