#include "Box.hpp"

Box::Box(){
    head = NULL;
}

Box::Box(const Box& oth){
    head = NULL;
    *this = oth;
}

Box& Box::operator=(const Box& oth){
    if (this != &oth){
        // if (head){
        //     mylist *tmp;
        //     while (head){
        //         tmp = head;
        //         head = head->next;
        //         delete tmp;
        //     }
        // }
        // head = oth.head;       
    }
    return *this;
}

mylist* Box::create_myl(AMateria *m){
    mylist *L = new(mylist);
    L->ptr = m;
    L->next = NULL;
    return L;
}

void Box::add(AMateria *m){
    if (!m)
        return ;
    if (!head)
        head = create_myl(m);
    else{
        mylist *tmp = head;
        while (tmp->next){
            if (tmp->ptr == m)
                return;
            tmp = tmp->next;
        }
        if (tmp->ptr == m)
            return;
        tmp->next = create_myl(m); 
    }
}

Box::~Box(){
    mylist *tmp;
    while (head){
        tmp = head;
        head = head->next;
        delete tmp->ptr;
        tmp->ptr = NULL;
        delete tmp;
    }
}