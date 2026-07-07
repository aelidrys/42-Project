#ifndef MUTANTSTACK
#define MUTANTSTACK

#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <limits>
#include <list>
#include <stack>

template<class T>
class MutantStack: public std::stack<T>
{	
public:
	typedef typename std::stack<T>::container_type::iterator iterator;

	MutantStack(){
		return;
	}
	MutantStack(const MutantStack& oth): std::stack<T>(oth){
		*this = oth;
	}
	MutantStack& operator=(const MutantStack& oth){
		std::stack<T>::operator=(oth); 
		return *this;
	}
	iterator begin(){
		return this->c.begin();
	}
	iterator end(){
		return this->c.end();
	}
	~MutantStack(){
		;
	}
};

#endif