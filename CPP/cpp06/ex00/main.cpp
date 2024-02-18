#include "ScalarConverter.hpp"


int main(int ac, char **av){
    if (ac == 1)
        return 0;
    ScalarConverter::convert(av[1]);
}