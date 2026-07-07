#include <stdio.h>
#include <stdlib.h>

int p() {
    char buffer[64];
    unsigned int ret_ptr;

    fflush(stdout);
    gets(buffer);
    
    ret_ptr = __builtin_return_address(0);
    if ((ret_ptr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", (void *)ret_ptr); // 0x8048620 is likely a format string "(%p)\n"
        _exit(1);
    }
    
    puts(buffer);
    return strdup(buffer);
}

int main(){
    p();
}
