#include <iostream>
#include <algorithm>

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

template<typename T>
long easyfind(T array, int second){
	size_t indx = std::distance(array.begin(), std::find(array.begin(), array.end(), second));
	if (indx != array.size()){
		std::cout<<"the integr: "<<second<<" exist in index: "<<indx<<std::endl;
		return indx;
	}
	std::cout<<"the Second parameter Not exist in the array"<<std::endl;
	return -1;
}

#endif