#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <cfloat>
#include <cmath>

class ScalarConverter
{
static int i_v;
static float f_v;
static double d_v;
static char c;
ScalarConverter();
ScalarConverter(const ScalarConverter& oth);
ScalarConverter& operator=(const ScalarConverter& oth);
static int isChar(std::string arg);
static int isInt(const std::string& arg);
static int isFraction(const std::string& arg);
static void display(const double& x, const std::string& arg);
static int isPseudo(const std::string& arg);
public:
    ~ScalarConverter();
    static void convert(const std::string& arg);
};

#endif