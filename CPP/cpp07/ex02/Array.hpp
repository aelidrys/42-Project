#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>

template<typename T>
class Array
{
T *array;
unsigned int len;
public:
    Array(){
		len = 0;
        array = NULL;
    }
    Array(unsigned int n){
        len = n;
        array = new T[n];
    }
    Array(const Array& oth){
		len = 0;
		array = NULL;
        *this = oth;
    }
    Array& operator=(const Array& oth){
		if (len)
			delete[] array;
		array = NULL;
		len = oth.len;
		if (len){
			array = new T[len];
			for (unsigned int i = 0; i < len; i++)
				array[i] = oth.array[i];
		}
		return *this;
	}
	T& operator[](long index) const{
		if (!len || index < 0 || index >= len)
			throw std::out_of_range("index out of range");
		return (array[index]);
	}
	unsigned int size() const{
		return len;
	}
	~Array(){
		if (len)
			delete[] array;
	}
};

#endif