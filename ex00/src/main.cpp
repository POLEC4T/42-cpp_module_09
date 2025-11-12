/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miloniemaz <mniemaz@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:13:30 by miloniemaz        #+#    #+#             */
/*   Updated: 2025/11/12 10:23:14 by miloniemaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>

/**\
 * date must be YYYY-M(M)-D(D)
 */
static bool isDateValid(std::string& date) {
	int year = 0;
	int month = 0;
	int day = 0;

	std::istringstream iss;

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

	iss.str(date.substr(0, firstDashPos));
	iss >> year;
	if (iss.fail() || !iss.eof())
		return false;

	iss.clear();
	std::string monthStr = date.substr(firstDashPos + 1, secondDashPos - (firstDashPos + 1));
	iss.str(monthStr);
	iss >> month;
	if (iss.fail() || !iss.eof())
		return false;
	iss.clear();
	if (monthStr.size() == 1) {
		date.insert(firstDashPos + 1, "0");
		++secondDashPos;
	}

	
	std::string dayStr = date.substr(secondDashPos + 1, date.size() - (secondDashPos + 1));
	iss.str(dayStr);
	iss >> day;
	if (iss.fail() || !iss.eof())
		return false;
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

static int parseDB(std::map<std::string, int>& dbcontent) {
	std::ifstream data("test.csv");
	
	if (!data.is_open() || data.fail()) {
		std::cerr << "Error: Could not open " << DBFILENAME << " file" << std::endl;
		return (EXIT_FAILURE);
	}

	std::string date;
	float value;
	std::string line;
	std::istringstream iss;
	getline(data, line);

	size_t commapos;
	while (getline(data, line)) {

		commapos = line.find(',');
		if (commapos == std::string::npos) {
			std::cerr << "Error: missing comma: " << line << std::endl;
			return (EXIT_FAILURE);
		}

		date = line.substr(0, commapos);
		if (!isDateValid(date)) {
			std::cerr << "Error: bad date: " << line << std::endl;
			return (EXIT_FAILURE);
		}

		
		iss.str(line.substr(commapos + 1));
		iss >> value;
		if (!iss.eof() || iss.fail() || value < 0) {
			std::cerr << "Error: bad value: " << line << std::endl;
			return (EXIT_FAILURE);
		}
		iss.clear();

		dbcontent.insert(std::make_pair(date, value));
		
	}

	return (EXIT_SUCCESS);
}

int main(void) {
	std::map<std::string, int> dbcontent;
	if (parseDB(dbcontent) == EXIT_FAILURE) {
		return (EXIT_FAILURE);
	}

	std::map<std::string, int>::iterator it;
	for (it = dbcontent.begin(); it != dbcontent.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}


	return (EXIT_SUCCESS);
}
