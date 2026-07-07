#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <time.h>
#include <sys/time.h> 
#include <string>

class PmergeMe
{
int is_odd;
double v_time;
int x;
double d_time;
std::vector<int> main_v;
std::vector<std::pair<int,int> > pairs;
std::deque<int> main_d;
std::deque<std::pair<int,int> > d_pairs;
public:
    PmergeMe();
    void insert_v(std::vector<int>& v0, int a);
    void insertion_sort_v_pairs(int i);
    void store_and_sorting_v(char **arg, int ac);
    void sorting_v();

    void insert_d(std::deque<int>& v0, int a);
    void insertion_sort_d_pairs(int i);
    void store_and_sorting_d(char **arg, int ac);
    void sorting_d();

    void display(int ac);
    void error_handle(const std::string& error);
    void is_valid(const std::string& arg);
    int  is_sorted(std::vector<int>& v1);
    PmergeMe(const PmergeMe& oth);
    PmergeMe& operator=(const PmergeMe& oth);
    ~PmergeMe();
};

#endif