#include <stdio.h>
#include <stdlib.h>


int m = 0;//0x8049810 => \x10\x98\x04\x08

void p(char *buffer){
    printf(buffer);
}


void n(){
    char buffer[512];
    fgets(buffer, 512, stdin);
    p(buffer);
    if (m == 16930116){
        system("/bin/cat /home/user/level5/.pass");
    }
}

int main(){
    n();
}