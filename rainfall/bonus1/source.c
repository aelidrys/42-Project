#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
    char buffer[40];
    int size;
    size = atoi(av[1]);

    if (size > 9) {
        return 1;
    }

    memcpy(buffer, av[2], size * 4);

    // 0x574f4c46 translated to ASCII text is "FLOW"
    if (size == 0x574f4c46) {
        execl("/bin/sh", "sh", NULL); 
    }

    return 0;
}