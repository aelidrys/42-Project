#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>
#include <limits>
#include <list>

#ifndef SPAN_HPP
#define SPAN_HPP

class Span
{
unsigned int len; 
std::vector<int> cntiner;
public:
    Span();
    Span(unsigned int N);
    Span(const Span& oth);
    Span& operator=(const Span& oth);
    void addNumber(int x);
    int shortestSpan() const;
    int longestSpan() const;
    void display();
    ~Span();
    template<typename iTer>
    void add(iTer begin, iTer end){
        while (end != begin)
            addNumber(*(begin++));
    }
};

#endif