#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <aio.h>

int m = 0;

void v(){
    char buffer[512];
    
    fgets(buffer, 512, stdin);
    printf(buffer);

    if (m == 64){
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
}


int main(){
    v();
}
