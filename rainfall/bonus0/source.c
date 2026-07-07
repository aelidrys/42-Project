#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void p(char *dest, char *prompt) {
    char buffer[4096]; // 0x1000 bytes
    puts(prompt);
    read(0, buffer, 4096);
    
    // Replaces the first newline character with a null terminator
    char *newline = strchr(buffer, '\n');
    if (newline) *newline = '\0'; 
    
    // Vulnerability? Only copies up to 20 (0x14) bytes safely!
    strncpy(dest, buffer, 20);
}

void pp(char *main_buffer) {
    char local1[20]; // at (%ebp)-0x30 (48 in decimal) -> room for 20 bytes
    char local2[20]; // at (%ebp)-0x1c (28 in decimal) -> room for 20 bytes
    
    p(local1, " - \n");
    p(local2, " - \n");
    
    strcpy(main_buffer, local1); 
    
    int len = strlen(main_buffer);
    short *end = (short*)(main_buffer + len);
    *end = ' ';
    // (gdb) x/s 0x80486a4
    // 0x80486a4:       " "
    
    strcat(main_buffer, local2);
}
 
int main() {
    char main_buffer[42];
    pp(main_buffer);
    puts(main_buffer);
    return 0;
}
