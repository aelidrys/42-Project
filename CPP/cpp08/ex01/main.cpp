#include "Span.hpp"

int main(){

    // Span sp = Span(5);
    // sp.addNumber(6);
    // sp.addNumber(3);
    // sp.addNumber(17);
    // sp.addNumber(9);
    // sp.addNumber(11);
    // std::cout << sp.shortestSpan() << std::endl;
    // std::cout << sp.longestSpan() << std::endl;


    Span span(15);
    try{
        for (unsigned int i = 0; i < 10; i++)
            span.addNumber(i*i+2*i+1);
        
        span.display();
        std::cout<<"ShortestSpan = "<<span.shortestSpan()<<std::endl;
        std::cout<<"LongestSpan  = "<<span.longestSpan()<<std::endl;
        std::list<int> A;
        std::cout<<std::endl;
        for (size_t i = 0; i < 5; i++){
            A.push_back(i);
        }
        span.add(A.begin(), A.end());
        span.display();
    }
    catch(std::exception& exp)
    {
        std::cout<<exp.what()<<std::endl;
    }
}