/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:13:28 by miloniemaz        #+#    #+#             */
/*   Updated: 2025/11/13 15:42:09 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) {
	(void)copy;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	(void)other;
	return *this;
}

/**
 * @brief puts str into val.
 * str must be of type T, otherwise returns false.
 * @example "42" -> true, "42abc" -> false, " 42" -> false, "4.2" -> false
 */
template <typename T>
bool ftStrToT(T& val, std::string& str) {
	std::istringstream iss(str);
	if (std::iswspace(iss.peek()))
		return false;
	iss >> val;
	if (iss.fail() || !iss.eof())
		return false;
	return (true);
}

/**\
 * date must be YYYY-M(M)-D(D)
 */
bool isDateValid(std::string& date) {
	int year = 0;
	int month = 0;
	int day = 0;

	std::string dayStr;
	std::string monthStr;
	std::string yearStr;

	size_t firstDashPos = date.find('-');
	if (firstDashPos == std::string::npos)
		return (false);
	size_t secondDashPos = date.find('-', firstDashPos + 1);
	if (secondDashPos == std::string::npos)
		return (false);
	size_t lastDashPos = date.rfind('-');
	bool oneDash = firstDashPos == lastDashPos;
	bool tooMuchDashes = secondDashPos != lastDashPos;
	if (oneDash || tooMuchDashes)
		return (false);

	yearStr = date.substr(0, firstDashPos);
	if (ftStrToT(year, yearStr) == false)
		return (false);

	monthStr = date.substr(firstDashPos + 1, secondDashPos - (firstDashPos + 1));
	if (ftStrToT(month, monthStr) == false)
		return (false);
	if (monthStr.size() == 1) {
		date.insert(firstDashPos + 1, "0");
		++secondDashPos;
	}

	dayStr = date.substr(secondDashPos + 1, date.size() - (secondDashPos + 1));
	if (ftStrToT(day, dayStr) == false)
		return (false);
	if (dayStr.size() == 1)
		date.insert(secondDashPos + 1, "0");

	if (year < 0 || (month < 1 || month > 12) || (day < 1 || day > 31))
		return (false);

	int maxday;
	bool isLeapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
	if (isLeapYear && month == 2)
		maxday = 29;
	else if (month == 2)
		maxday = 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		maxday = 30;
	else
		maxday = 31;

	return (day <= maxday);
}

int BitcoinExchange::parseFile(const std::string& filename, t_file_type filetype) {
	std::ifstream data(filename.c_str());
	
	if (!data.is_open() || data.fail()) {
		std::cerr << "Error: Could not open " << filename << " file" << std::endl;
		return (EXIT_FAILURE);
	}

	std::string delimiter = (filetype == DB ? "," : " | ");
	std::string date;
	float value;
	std::string line;
	getline(data, line);

	size_t delimpos;
	while (getline(data, line)) {

		delimpos = line.find(delimiter);
		if (delimpos == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			if (filetype == INPUT)
				continue ;
			return (EXIT_FAILURE);
		}

		date = line.substr(0, delimpos);
		if (!isDateValid(date)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			if (filetype == INPUT)
				continue ;
			return (EXIT_FAILURE);
		}

		std::string valueStr = line.substr(delimpos + delimiter.size());
		if (ftStrToT(value, valueStr) == false) {
			std::cerr << "Error: bad value => " << line << std::endl;
			
			if (filetype == INPUT)
				continue ;
			return (EXIT_FAILURE);
		}
		if (filetype == INPUT) {
			if (value > 1000) {
				std::cerr << "Error: too large a number" << std::endl;
				continue;
			}
			if (value < 0) {
				std::cerr << "Error: not a positive number" << std::endl; 
				continue ;
			}
		}
		if (filetype == DB)
			_db.insert(std::make_pair(date, value));
		else /* if type == INPUT */ {
			std::map<std::string, float>::iterator it;
			
			it = _db.lower_bound(date);
			bool isBeforeLowest = it == _db.begin() && it->first != date;
			if (isBeforeLowest) {
				std::cerr << "Error: no date available before " << date << std::endl;
				continue;
			}

			bool isAfterGreatest = it == _db.end();

			if (isAfterGreatest || it->first != date)
				--it;

			// 2012-01-11 => 1 = 7.1
			
			
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
		}
	}

	return (EXIT_SUCCESS);
}

void BitcoinExchange::printDB() const {
	std::map<std::string, float>::const_iterator it = _db.begin();
	std::map<std::string, float>::const_iterator ite = _db.end();

	for (; it != ite; ++it) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
}




