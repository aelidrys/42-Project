#include<stdio.h>
#include<stdlib.h>

int main(){
    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    int input;
    printf("Password:");
    scanf("%d", &input);
    if (input == 5276){
        puts("\nAuthenticated!");
        system("/bin/sh");
        return 0;
    }
    else {
        puts("\nInvalid Password!");
        return 1;
    }
}