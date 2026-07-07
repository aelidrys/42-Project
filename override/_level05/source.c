#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[100];
    int i;

    // Read up to 100 bytes safely
    fgets(buf, 100, stdin);

    // Loop through the string and lower-case all uppercase letters
    for (i = 0; i < strlen(buf); i++) {
        if (buf[i] >= 'A' && buf[i] <= 'Z') {
            buf[i] = buf[i] ^ 0x20;
        }
    }

    // THE VULNERABILITY: Format string bug
    printf(buf); 

    exit(0);
}