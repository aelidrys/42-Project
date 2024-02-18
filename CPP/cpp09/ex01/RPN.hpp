#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <sstream>


int     do_op(int a, int b, int op);
void    rpn(std::stack<int>& mstack, int op);
int     is_operator(std::string s1);
void    check_input(std::string& input);

#endif