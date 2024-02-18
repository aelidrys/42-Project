#include "BitcoinExchange.hpp"

void store_data(std::map<std::string, float>& map){
	std::string date;
	std::string value;
	std::fstream data_file;

	data_file.open("data.csv", std::ios::in);
	std::getline(data_file, date);
	while (std::getline(data_file, date, ',')){
		std::getline(data_file, value);
		map[date] = std::strtod(value.c_str(),NULL);
	} 
}


void btc_value(std::map<std::string, float>& map, std::string key, float btc_v){
	if (btc_v == -1)
		return;
	std::map<std::string, float>::iterator it;
	it = map.begin();
	if (it->first.size() > key.size() || (it->first > key
		&& it->first.size() == key.size())){
		std::cout<<"Error: no date less than "<<key<<"\n";
		return ;
	}
	it = map.end();
	it--;
	if (it->first.size() < key.size() || (it->first < key
		&& it->first.size() == key.size())){
		std::cout<<key<<" => "<<btc_v<<" = "<<it->second * btc_v<<"\n";
		return ;
	}
	for (it = map.begin(); it != map.end(); it++){
		if (it->first >= key){
			if (it->first == key)
				std::cout<<key<<" => "<<btc_v<<" = "<<it->second * btc_v<<"\n";
			else if (it != map.begin())
				std::cout<<key<<" => "<<btc_v<<" = "<<(--it++)->second * btc_v<<"\n";
			return ;
		}
	}
}


void read_input(const char *str, std::map<std::string, float>& map){
	std::fstream in_f;
	std::string line;
	std::string key;
	std::stringstream sline;

	in_f.open(str, std::ios::in);
	if (!in_f.is_open()){
		std::cout<<"Error: file "<<str<<" cannot open.\n";
		return ;
	}
	if (!std::getline(in_f, line)){
		std::cout<<"Error: "<<str<<" file is empty.\n";
		return ;
	}
	if (line != "date | value" && line != "date|value")
		std::cout<<"Error: bad title.\n";
	while (std::getline(in_f, line)){
		if (line.find('|') == line.npos){
			if (line != "")
				std::cout<<"Error: invalid format.\n";
			continue;
		}
		sline<<line;
		std::getline(sline,key, ' ');
		sline.clear();
		sline.str("");
		sline<<line;
		btc_value(map, key, check_input(sline,key));
		sline.clear();
		sline.str("");
	}
	
}


int check_date(std::stringstream &line, std::string key){
	std::stringstream ss;
	std::string s0[3];
	long year = 0;
	int month = 0;
	int day = 0;
	char dlm[3];


	ss<<key;
	std::getline(ss,s0[0],'-');
	std::getline(ss,s0[1],'-');
	std::getline(ss,s0[2],' ');
	line>>year>>dlm[0]>>month>>dlm[1]>>day;
	if (month <= 0 || month > 12 || day <= 0 || day > 31 || s0[1].size() != 2
		|| dlm[0] != '-' || dlm[1] != '-' || s0[2].size() != 2 || year <= 0)
		return 0;

	return (is_number(s0[0],0) && is_number(s0[1],0) && is_number(s0[2],0));
}


int is_number(std::string str, int fraction)
{
	size_t a = 0;
	while (fraction && (str[a] == ' ' || str[a] == '-' || str[a] == '+')){
		if (str[a] == '-' || str[a] == '+'){
			a++;break ;
		}
		a++;
	}
	if (a == str.size())
		return 0;
	for (size_t i = a; i < str.size(); i++)
		if (!std::isdigit(str[i]))
			if (str[i] != '.' || !fraction)
				 return 0;
	return 1;
}


float check_input(std::stringstream &line, std::string key){
	float b;
	std::string btc;
	if (!check_date(line,key)){
		std::cout<<"Error: bad input => "<<key<<"\n";
		return -1;
	}
	std::getline(line, btc, ' ');
	std::getline(line, btc, '|');
	for (size_t i= 0; i < btc.size(); i++)
		if (btc[i] != ' '){
			std::cout<<"Error: invalid format.\n";
			return - 1;
		}
	std::getline(line, btc);
	b = strtod(btc.c_str(), NULL);
	if (btc == "" || b < 0 || b > 1000 || !is_number(btc,1)){
		if (btc == "")
			std::cout<<"Error: no bitcoin value.\n";
		if (b < 0)
			std::cout<<"Error: not a positive number.\n";
		if (b > 1000)
			std::cout<<"Error: too large a number.\n";
		if (!is_number(btc,1))
			std::cout<<"Error: invalid btc_value.\n";

		return -1;
	}
	// std::cout<<key<<" => "<<b<<" = ";
	return b;
}
