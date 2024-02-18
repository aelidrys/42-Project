#include "RPN.hpp"

void check_input(std::string& input){
	if (input.size() != 1 || (!is_operator(input) && !std::isdigit(input[0]))){
			std::cout<<"Error: invalid input.\n";
			exit(1);
	}
}

int is_operator(std::string s1){
	if (s1 == "*")
		return '*';
	if (s1 == "/")
		return '/';
	if (s1 == "-")
		return '-';
	if (s1 == "+")
		return '+';
	return 0;
}

int do_op(int a, int b, int op){
	if (op == '*')
		return (a * b);
	if (op == '-')
		return (a - b);
	if (op == '+')
		return (a + b);
	if (op == '/')
		return (a / b);
	return (0);
}

void	rpn(std::stack<int>& mstack, int op){
	int first = 0;
	int second = 0;
	if (!op)
		return ;
	if (mstack.size() < 2){
		std::cout<<"Error: operations not compatible with numbers.\n";
		exit(1);
	}
	second = mstack.top();
	mstack.pop();
	first = mstack.top();
	mstack.pop();
	mstack.push(do_op(first, second, op));
}
