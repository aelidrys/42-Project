#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){
	;
}

PmergeMe::PmergeMe(const PmergeMe& oth){
	*this = oth;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& oth){
	if (this != &oth){
		main_v = oth.main_v;
		main_d = oth.main_d;
	}
	return *this;
}

void PmergeMe::error_handle(const std::string& error){
	std::cout<<"Error: "<<error<<".\n";
	exit(1);
}

void PmergeMe::is_valid(const std::string& arg){
	size_t a = 0;
	while (a < arg.size() && arg[a] == ' ')
		a++;
	if (arg[a] == '+')
		a++;
	if (a == arg.size())
		error_handle("invalid argement");
	for (size_t i = a; i < arg.size(); i++)
		if (!isdigit(arg[i]))
			error_handle("invalid argement");
	if (std::strtod(arg.c_str(), NULL) > 2147483647)
		error_handle("too large number");
}

int  PmergeMe::is_sorted(std::vector<int>& v1){
	for (size_t i = 0; i+1 < v1.size(); i++)
		if (v1[i] > v1[i+1])
			return 0;
	return 1;
	
}

void PmergeMe::store_and_sorting_v(char **arg, int ac){
	clock_t t1, t2;
	t1 = clock();
	for (int i = 0; i+1 < ac; i += 2)
		pairs.push_back(std::make_pair(atoi(arg[i]), atoi(arg[i+1])));
	is_odd = 0;
	if (ac % 2){
		is_odd = 1;
		x = atoi(arg[ac-1]);
	}
	sorting_v();
	t2 = clock();
	v_time = (t2-t1)/1000.0;
}

void PmergeMe::sorting_v(){
	std::vector<int> pend_v;

	for (size_t i = 0; i < pairs.size(); i++)
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);

	for (size_t i = 0; i+1 < pairs.size(); i++)
		insertion_sort_v_pairs(i);

	for (size_t i = 0; i < pairs.size(); i++){
		pend_v.push_back(pairs[i].first);
		main_v.push_back(pairs[i].second);
	}

	
	main_v.insert(main_v.begin(),*pend_v.begin());
	for (size_t i = 1; i < pend_v.size(); i++)
		insert_v(main_v,pend_v[i]);
	if (is_odd)
		insert_v(main_v,x); 
}

void PmergeMe::insert_v(std::vector<int>& v0, int a){
   std::vector<int>::iterator it;
	for (it = v0.begin(); it != v0.end(); it++){
		if (a < *it){
            v0.insert(it,a);
            return ;
        }
	}
    v0.insert(v0.end(),a);
}

void PmergeMe::insertion_sort_v_pairs(int i){
	if (i >= 0 && pairs[i].second > pairs[i+1].second){
		std::swap(pairs[i], pairs[i+1]);
		insertion_sort_v_pairs(i-1);
	}
}


void PmergeMe::store_and_sorting_d(char **arg, int ac){
	clock_t t1, t2;
	t1 = clock();
	for (int i = 0; i+1 < ac; i += 2)
		d_pairs.push_back(std::make_pair(atoi(arg[i]), atoi(arg[i+1])));
	is_odd = 0;
	if (ac % 2){
		is_odd = 1;
		x = atoi(arg[ac-1]);
	}
	sorting_d();
	t2 = clock();
	d_time = (t2-t1)/1000.0;
}

void PmergeMe::sorting_d(){
	std::vector<int> pend_d;

	for (size_t i = 0; i < d_pairs.size(); i++)
		if (d_pairs[i].first > d_pairs[i].second)
			std::swap(d_pairs[i].first, d_pairs[i].second);

	for (size_t i = 0; i+1 < d_pairs.size(); i++)
		insertion_sort_d_pairs(i);

	for (size_t i = 0; i < d_pairs.size(); i++){
		pend_d.push_back(d_pairs[i].first);
		main_d.push_back(d_pairs[i].second);
	}
	
	main_d.insert(main_d.begin(),*pend_d.begin());
	for (size_t i = 1; i < pend_d.size(); i++)
		insert_d(main_d,pend_d[i]);
	if (is_odd)
		insert_d(main_d,x); 
}

void PmergeMe::insert_d(std::deque<int>& d0, int a){
	std::deque<int>::iterator it;
	for (it = d0.begin(); it != d0.end(); it++){
		if (a < *it){
            d0.insert(it,a);
            return ;
        }
	}
    d0.insert(d0.end(),a);
}

void PmergeMe::insertion_sort_d_pairs(int i){
	if (i >= 0 && d_pairs[i].second > d_pairs[i+1].second){
		std::swap(d_pairs[i], d_pairs[i+1]);
		insertion_sort_d_pairs(i-1);
	}
}

void PmergeMe::display(int ac){
	std::cout<<"\nAfter: ";
	for (size_t i = 0; i < main_d.size(); i++)
		std::cout<<main_d[i]<<" ";
	std::cout<<"\n\n";
	std::cout<<"Time to process a range of "<<ac<<" elements ";
	std::cout<<"with std::deque  : "<<std::to_string(d_time)<<" ms\n";
	std::cout<<"Time to process a range of "<<ac<<" elements ";
	std::cout<<"with std::vector : "<<std::to_string(v_time)<<" ms\n";
}

PmergeMe::~PmergeMe(){
	;
}