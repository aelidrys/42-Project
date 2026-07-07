#include "Span.hpp"

Span::Span(){
    len = 0;
}

Span::Span(unsigned int N){
    len = N;
}

Span::Span(const Span& oth){
    *this = oth;
}

Span& Span::operator=(const Span& oth){
    if (this != &oth){
        len = oth.len;
        cntiner = oth.cntiner;
    }
    return *this;
}

void Span::addNumber(int x){
    if (cntiner.size() < len)
        cntiner.push_back(x);
    else
        throw std::out_of_range("No space left");
}

int Span::shortestSpan() const{
    int min = std::numeric_limits<int>::max();
	std::vector<int> SortedContiner = cntiner;
	std::sort(SortedContiner.begin(), SortedContiner.end());
    if (cntiner.size() < 2){
        throw std::out_of_range("No Span possible");
    }
	for (unsigned int i = 0; i + 1 < cntiner.size(); i++){
		if (SortedContiner[i+1] - SortedContiner[i] < min)
			min = SortedContiner[i+1] - SortedContiner[i];
	}
    return (min);
}

int Span::longestSpan() const{
    if (cntiner.size() < 2)
        throw std::out_of_range("No Span possible");
    int max = *std::max_element(cntiner.begin(), cntiner.end());
    int min = *std::min_element(cntiner.begin(), cntiner.end());
    return(max - min);
}

void Span::display(){
    for (unsigned int i = 0; i < cntiner.size(); i++)
        std::cout<<cntiner[i]<<std::endl;
}


Span::~Span(){
    ;
}