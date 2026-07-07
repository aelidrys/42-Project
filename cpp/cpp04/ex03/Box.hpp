#include "AMateria.hpp"

#ifndef BOX_HPP
#define BOX_HPP

class AMateria;

typedef struct my_list
{
    AMateria		*ptr;
	struct my_list	*next;
} mylist;

class Box
{
mylist	*head;
mylist	*create_myl(AMateria *m);
Box&	operator=(const Box& oth);
public:
	Box();
	Box(const Box& oth);
	void add(AMateria *m);
	~Box();
};

#endif