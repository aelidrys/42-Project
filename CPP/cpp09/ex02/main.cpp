#include "PmergeMe.hpp"

int main(int ac, char **av){
    std::vector<int> v1;
    PmergeMe merge;
    for (int i = 1; av[i]; i++){
        merge.is_valid(av[i]);
        v1.push_back(atoi(av[i]));
    }
    if (ac == 1 || ac == 2 || merge.is_sorted(v1))
        return 0;
    std::cout<<"Before: ";
    for (int i = 1; av[i]; i++)
        std::cout<<(atoi(av[i]))<<" ";
    std::cout<<"\n";
    merge.store_and_sorting_v(av+1, ac-1);
    merge.store_and_sorting_d(av+1, ac-1);
    merge.display(ac-1);
}