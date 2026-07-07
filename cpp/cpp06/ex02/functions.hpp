#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <stdexcept>
#include <stdlib.h>
#include <sys/time.h>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base    *generate(void);
void    identify(Base* p);
void    identify(Base& p);

#endif