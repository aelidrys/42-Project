#include<stdio.h>
#include<stdlib.h>
#include <string.h>


void m(){
    puts("Nope");
}

void n(){
    system("/bin/cat /home/user/level7/.pass");
}

int main(int ac, char **av){
    char *buf = malloc(64);
    void (**fun_ptr)() = malloc(4);

    *fun_ptr = &m;

    strcpy(buf, av[1]);

    (*fun_ptr)();
}