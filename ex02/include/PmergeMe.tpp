/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:12:20 by mniemaz           #+#    #+#             */
/*   Updated: 2025/11/24 12:50:18 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <iomanip>
#define GREEN "\033[32m"
#define ORANGE "\033[35m"
#define END "\033[0m"

template<typename Container>
PmergeMe<Container>::PmergeMe() {}

template<typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe<Container>& copy) {
	(void)copy;
}

template<typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator=(const PmergeMe<Container>& other) {
	(void)other;
	return (*this);
}

template<typename Container>
PmergeMe<Container>::~PmergeMe() {}

template<typename Container>
void PmergeMe<Container>::printContainer(const std::string& name, const Container& cont, long toColor, const std::string& color) {
	std::cout << name;
	for (typename Container::const_iterator it = cont.begin(); it < cont.end(); ++it) {
		if (std::distance(cont.begin(), it) > NB_PRINT_NUMS) {
			std::cout << "...";
			break;
		}
		if (*it == toColor)
			std::cout << color << *it << END << " ";
		else
			std::cout << *it << " ";
	}
	std::cout << "\n";
}

template<typename Container>
void PmergeMe<Container>::_swapItValues(typename Container::iterator it1, typename Container::iterator it2) {
	long temp = *it1;
	*it1 = *(it2);
	*(it2) = temp;
}

/**
 * @brief reverse a part of a container
 * @note ite is `last of cont to rev` + 1 => ite is not included in the part to reverse
 * @example it becomes ite - 1, it + 1 becomes ite - 2 etc
 */
template<typename Container>
void PmergeMe<Container>::_reverseContPart(typename Container::iterator& it, typename Container::iterator& ite) {
	size_t size = ite - it;
	typename Container::iterator start = it;
	typename Container::iterator end = ite - 1;
	for (size_t i = 0; i < size / 2; ++i) {
		_swapItValues(start, end);
		++start;
		--end;
	}
}

/**
 * @brief get the jacobsthal order for size elements
 * @returns a container with the indices in jacobsthal order
 * 														0 1 2 3 4 5 6
 * @example size = 7: jacob = [(0,1,)1,3,5] => returns [0,2,1,4,3,6,5]
 * @details Jacobsthal numbers gives intervals to to reverse parts of the
 * 			initial ordered indices to get the jacobsthal order.
 */
template<typename Container>
Container PmergeMe<Container>::_getJacobsthalOrder(long size) {
	Container jacob;
	if (size >= 0)
		jacob.push_back(0);
	if (size >= 1)
		jacob.push_back(1);

	long nextnum = 0;
	long i = jacob.size();
	while (1) {
		nextnum = jacob[i - 1] + 2 * jacob[i - 2];
		if (nextnum > size)
			break;
		jacob.push_back(nextnum);
		++i;
	}

	// erase first 0 and 1, never useful
	jacob.erase(jacob.begin());
	jacob.erase(jacob.begin());

	Container order;
	for (size_t i = 0; i < (size_t)size; ++i)
		order.push_back(i);

	for (size_t i = 0; i < jacob.size() - 1; ++i) {
		typename Container::iterator start = order.begin() + jacob[i];
		typename Container::iterator end = order.begin() + jacob[i + 1];
		_reverseContPart(start, end);
	}
	typename Container::iterator start = order.begin() + jacob.back();
	typename Container::iterator end = order.end();
	_reverseContPart(start, end);

	return (order);
}

template<typename Container>
void PmergeMe<Container>::_setMainAndPending(Container& cont, Container& main, Container& pending) {
	Container unsortedBigs;
	// sort pairs themselves and fill unsortedBigs 
	for (typename Container::iterator it = cont.begin(); it < cont.end(); it += 2) {
		if (*(it + 1) > *it)
			_swapItValues(it + 1, it);
		unsortedBigs.push_back(*it);
	}

	main = _processSort(unsortedBigs);

	for (typename Container::iterator it = main.begin(); it < main.end(); ++it) {
		typename Container::iterator bigIt = std::find(cont.begin(), cont.end(), *it);
		typename Container::value_type& smallVal = *(bigIt + 1);
		pending.push_back(smallVal);
	}
}

template<typename Container>
void PmergeMe<Container>::_fillMainInOrder(Container& main, Container& pending, typename Container::value_type& lastSingleNum) {
	Container order = _getJacobsthalOrder(pending.size());

	if (PRINT_LOGS) {
		std::cout << "\n### RECURSIVE CALL ###" << std::endl;
		printContainer("jacobsthal order:\t", order, -1, "");
		printContainer("pending:\t\t", pending, -1, "");
		printContainer("main:\t\t\t", main, -1, "");
		if (lastSingleNum != -1)
			std::cout << "last single num:\t" << lastSingleNum << std::endl;
		std::cout << "\nfirst pending always pos 0 because always smaller than his big:" << std::endl;
	}

	const Container constMain = main;
	
	main.insert(main.begin(), pending[order[0]]);
	
	if (PRINT_LOGS) {
		printContainer("new main:\t\t", main, pending[order[0]], GREEN);
		std::cout << "\n";
	}
	
	for (size_t i = 1; i < order.size(); ++i) {
		typename Container::iterator bigIt = std::find(main.begin(), main.end(), constMain[order[i]]);
		_insertValSorted(main, pending[order[i]], main.begin(), bigIt);
	}

	if (lastSingleNum != -1) {
		if (PRINT_LOGS)
			std::cout << "(last single num)"<< std::endl;
		_insertValSorted(main, lastSingleNum, main.begin(), main.end());
	}
}

/**
 * @returns the iterator of the lowest in the above range of val (where it should be inserted)
 * @example val = 3, container = [1,2,4] => returns the iterator of 4 
 */
template<typename Container>
typename Container::iterator PmergeMe<Container>::_binarySearch(typename Container::iterator first, typename Container::iterator last, const long& val) {
	typename Container::iterator mid;
	size_t size;

	--last;
	while (first <= last) {
		size = (last - first) + 1;
		mid = first + (size / 2);

		if (val >= *mid)
			first = mid + 1;
		else
			last = mid - 1;
	}
	return (first);
}

size_t getNumSize(long num) {
	std::ostringstream oss;

	oss << num;
	if (oss.fail())
		throw std::invalid_argument("Error: getNumSize throw");
	return (oss.str().size());
	
}

template<typename Container>
void PmergeMe<Container>::_insertValSorted(Container& main, long val, typename Container::iterator startrange, typename Container::iterator endrange)
{
	if (PRINT_LOGS) {
		printContainer("curr main:\t\t", main, *endrange, ORANGE);
		std::cout << "range to insert " << GREEN << val << END << ":\t";
		for(size_t i = 0; i < (size_t)(endrange - startrange); ++i) {

			if (i > NB_PRINT_NUMS) {
				std::cout << " ...";
				break;
			}
			size_t numSize = getNumSize(*(startrange + i));

			for(size_t j = 0; j < numSize; ++j)
				std::cout << "↑";

			std::cout << (i + 1 == (size_t)(endrange - startrange) || (i + 1) == NB_PRINT_NUMS ? "" : "↑");
		}
		std::cout << "\n";
	}
	
	typename Container::iterator aboveRangeLowest = _binarySearch(startrange, endrange, val);
	main.insert(aboveRangeLowest, val);

	if (PRINT_LOGS) {
		printContainer("new main:\t\t", main, val, GREEN);
		std::cout << "\n";
	}

}

template<typename Container>
Container PmergeMe<Container>::_processSort(Container cont) {
	if (cont.size() == 1)
		return (cont);

	typename Container::value_type lastSingleNum = -1;
	Container main;
	Container pending;
	
	if (cont.size() % 2 == 1) {
		lastSingleNum = cont.back();
		cont.pop_back();
	}
	_setMainAndPending(cont, main, pending);
	_fillMainInOrder(main, pending, lastSingleNum);
	return (main);
}

#include <typeinfo>


template<typename Container>
double PmergeMe<Container>::FJASort(Container& args) {

	clock_t start;
	clock_t end;
	double elapsed;

	start = clock();

	args = _processSort(args);
	
	end = clock();

	elapsed = 1000.0 * (end - start) / CLOCKS_PER_SEC;
	return (elapsed);

}