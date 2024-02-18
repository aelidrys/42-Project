#include "RPN.hpp"

int main(int ac , char **av){
	std::string input;
	std::stringstream sinput;
	std::stack<int> mstack;
	if (ac != 2 || !av[1][0]){
		std::cout<<"Error: bad argement.\n";
		return 1;
	}
	sinput<<av[1];
	std::getline(sinput, input,' ');
	while (1){
		check_input(input);
		rpn(mstack,is_operator(input));
		if (!is_operator(input))
			mstack.push(atoi(input.c_str()));
		if (sinput.eof())
			break ;
		std::getline(sinput, input, ' ');
	}
	std::cout<<mstack.top()<<std::endl;
}