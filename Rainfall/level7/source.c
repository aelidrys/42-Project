#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
    int id;
    char *buffer;
};

void m() {
    // 0x8049960 is where fgets stored the flag from the file
    printf("%s - %d\n", (char *)0x8049960, time(NULL));
}

int main(int argc, char **argv) {
    // Allocation 1 & 2 (First Node Structure)
    struct node *n1 = malloc(8);       // stored at 0x1c(%esp)
    n1->id = 1;
    n1->buffer = malloc(8);            // n1->buffer is assigned here
    
    // Allocation 3 & 4 (Second Node Structure)
    struct node *n2 = malloc(8);       // stored at 0x18(%esp)
    n2->id = 2;
    n2->buffer = malloc(8);            // n2->buffer is assigned here
    
    // Vulnerability 1: Overflows n1->buffer and destroys n2's headers or pointers
    strcpy(n1->buffer, argv[1]);
    
    // Vulnerability 2: Overflows n2->buffer
    strcpy(n2->buffer, argv[2]);
    
    // Opens password file and stores it at global address 0x8049960
    FILE *f = fopen("/home/user/level8/.pass", "r"); // strings from 0x80486e9
    fgets((char *)0x8049960, 68, f);
    
    puts("~~");
    return 0; // address of ret 0x08048602 => \x02\x86\x04\x08
    // address of m: 0x080484f4 \xf4\x84\x04\x08
    // address of puts in GOT: 08049928 => \x28\x99\x04\x08
}
