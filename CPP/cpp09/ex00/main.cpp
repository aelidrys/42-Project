#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac == 1){
        std::cout<<"Error: could not open file.\n";
        return 1;
    }
    if (ac != 2)
        return 0;
    std::map<std::string, float> map;
    store_data(map);
    read_input(av[1], map);
}