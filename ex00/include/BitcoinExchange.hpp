/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 06:13:26 by miloniemaz        #+#    #+#             */
/*   Updated: 2025/11/13 16:05:10 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# define DBFILENAME "data.csv"
# include <map>
# include <string>

typedef enum e_file_type {
	DB,
	INPUT
} t_file_type;


class BitcoinExchange {
private:
	BitcoinExchange(const BitcoinExchange& copy);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	std::map<std::string, float> _db;
		
public:
	BitcoinExchange();
	~BitcoinExchange();
	int parseFile(const std::string& filename, t_file_type filetype);
	void printDB() const;
		
	
};

#endif