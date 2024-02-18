#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <map>

void	    store_data(std::map<std::string, float>& map);
int			is_number(std::string str, int fraction);
void	    read_input(const char *str, std::map<std::string, float>& map);
float	    check_input(std::stringstream &line, std::string key);
int		    check_date(std::stringstream &line, std::string key);
void        btc_value(std::map<std::string, float>& map, std::string key, float btc_v);
#endif