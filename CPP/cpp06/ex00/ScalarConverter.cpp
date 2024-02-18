#include "ScalarConverter.hpp"


int ScalarConverter::i_v = 0;
float ScalarConverter::f_v = 0;
double ScalarConverter::d_v = 0;
char ScalarConverter::c = '0';

ScalarConverter::ScalarConverter(){
	std::cout<<"ScalarConverter: Defult Constructor Called\n";
}

ScalarConverter::ScalarConverter(const ScalarConverter& oth){
	std::cout<<"ScalarConverter: Copy Constructor Called\n";
	*this = oth;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& oth){
	std::cout<<"ScalarConverter: Copy Assignment Called\n";
	if (this != &oth){
		;
	}
	return *this;
}


int ScalarConverter::isChar(std::string arg){
	if (arg.length() != 1)
		return 0;
	if (std::isdigit(arg[0]))
		return 0;
	return 1;
}

int ScalarConverter::isInt(const std::string& arg){
	size_t i = 0;
	while (arg[i] == ' ')
			i++;
	if (i < arg.length() && (arg[i] == '-' || arg[i] == '+'))
		i++;
	while (i < arg.length()){
		if (!std::isdigit(arg[i++]))
			return 0;
	}
	return 1;
}

int ScalarConverter::isFraction(const std::string& arg){
	size_t i = 0;
	int a = 0;
	int point = 0;
	while (arg[i] == ' ')
			i++;
	if (i < arg.length() && (arg[i] == '-' || arg[i] == '+'))
		i++;
	if (i < arg.length() && arg[i] == '.')
		return 0;
	if (arg[arg.length()-1] == 'f')
		a = 1;
	while (i < arg.length()-a){
		if (!std::isdigit(arg[i])){
			if (point || arg[i] != '.' || i == arg.length()-(a+1))
				return 0;
			point += (arg[i] == '.');
		}
		i++;
	}
	return point;
}


void ScalarConverter::display(const double& x, const std::string& arg){
	if (x > 255)
		std::cout<<"char: "<<"impossible"<<"\n";
	else if (std::isprint(c))
		std::cout<<"char: \'"<<c<<"\'\n";
	else
		std::cout<<"char: "<<"Non displayable"<<"\n";
	if (x > std::numeric_limits<int>::max() || x < std::numeric_limits<int>::min())
		std::cout<<"int: impossible\n";
	else
		std::cout<<"int: "<<i_v<<"\n";
	if (isFraction(arg) && long(x) != x){
		std::cout<<"float: "<<f_v<<"f\n";
		std::cout<<"double: "<<d_v<<"\n";
	}
	else if (isChar(arg)){
		std::cout<<"float: "<<f_v<<".0f\n";
		std::cout<<"double: "<<d_v<<".0\n";
	}
	else{
		std::cout<<"float: "<<x<<".0f\n";
		std::cout<<"double: "<<x<<".0\n";
	}
}

int ScalarConverter::isPseudo(const std::string& arg){
	if (arg == "nan" || arg == "nanf"){
		std::cout<<"char: impossible\n"<<"int: impossible\n";
		std::cout<<"float: nanf\n"<<"double: nan\n";
		return 1;
	}
	if (arg == "-inff" || arg == "+inff"){
		std::cout<<"char: impossible\n"<<"int: "<<arg[0]<<"inf"<<"\n";
		std::cout<<"float: "<<arg<<"\n"<<"double: "<<arg[0]<<"inf"<<"\n";
		return 1;
	}
	if (arg == "-inf" || arg == "+inf"){
		std::cout<<"char: impossible\n"<<"int: "<<arg<<"\n";
		std::cout<<"float: "<<arg<<"f\n"<<"double: "<<arg<<"\n";
		return 1;
	}
	return 0;
}

void ScalarConverter::convert(const std::string& arg){
	if (isPseudo(arg))
		return ;
	if (!arg.length())
		return ;
	if (isChar(arg)){
		c = arg[0];
		i_v = static_cast<int>(c);
		f_v = static_cast<float>(c);
		d_v = static_cast<double>(c);
		display(1,arg);
		return ;
	}
	if (isInt(arg)){
		i_v = atoi(arg.c_str());
		c = static_cast<char>(i_v);
		f_v = static_cast<float>(i_v);
		d_v = static_cast<double>(i_v);
	}
	else if (isFraction(arg)){
		if (arg[arg.length()-1] == 'f'){
			f_v = strtod(arg.c_str(), NULL);
			c = static_cast<char>(f_v);
			i_v = static_cast<int>(f_v);
			d_v = static_cast<double>(f_v);
		}
		else{
			d_v = strtod(arg.c_str(), NULL);
			c = static_cast<char>(d_v);
			i_v = static_cast<int>(d_v);
			f_v = static_cast<float>(d_v);
		}
	}
	else{
		std::cout<<"char: impossible\n"<<"int: impossible\n";
		std::cout<<"float: impossible\n"<<"double: impossible\n";
		return ;
	}		
	display(strtod(arg.c_str(),NULL),arg);
}

ScalarConverter::~ScalarConverter(){
	std::cout<<"ScalarConverter: Destructor Called\n";
}