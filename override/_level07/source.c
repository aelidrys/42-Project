#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clear_stdin(void)
{
    int c;

    while (1)
    {
        c = getchar();
        if (c == '\n' || c == EOF)
            break;
    }
}


unsigned int get_unum(void) {
    unsigned int num = 0;

    fflush(stdout); 
    scanf("%u", &num);
    clear_stdin();

    return num;
}    


int store_number(unsigned int *array) {
    unsigned int number;
    unsigned int index;

    printf(" Number: ");
    number = get_unum();
    printf(" Index: ");
    index = get_unum();

    if (index % 3 == 0) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil");
        puts(" *** ERROR! ***");
        return 1;
    }

    if ((number >> 24) == 0xb7) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    array[index] = number;
    return 0;
}

int read_number(unsigned int *array) {
    unsigned int index;

    printf(" Index: ");
    index = get_unum();

    printf(" Number at data[%u] is %u\n", index, array[index]);
    
    return 0;
}

int main(int argc, char **argv, char **envp) {
    unsigned int array[100] = {0}; 
    char command[20] = {0};
    int status = 0;

    while (*envp != NULL) {
        memset(*envp, 0, strlen(*envp));
        envp++;
    }

    while (*argv != NULL) {
        memset(*argv, 0, strlen(*argv));
        argv++;
    }

    puts("----------------------------------------------------");
    puts("  Welcome to wil's crappy number storage service!   ");
    puts("----------------------------------------------------");
    puts(" Commands:                                          ");
    puts("    store - store a number into the data storage    ");
    puts("    read  - read a number from the data storage     ");
    puts("    quit  - exit the program                        ");
    puts("----------------------------------------------------");
    puts("   wil has reserved some storage :>                 ");
    puts("----------------------------------------------------");

    while (1) {
        printf("Input command: ");
        
        fgets(command, 20, stdin);
        
        command[strlen(command) - 1] = '\0';

        if (strncmp(command, "store", 5) == 0) {
            status = store_number(array);
        } 
        else if (strncmp(command, "read", 4) == 0) {
            status = read_number(array);
        } 
        else if (strncmp(command, "quit", 4) == 0) {
            return 0;
        }

        if (status != 0) {
            printf(" Failed to do %s command\n", command);
        } else {
            printf(" Completed %s command successfully\n", command);
        }
        
        memset(command, 0, 20);
    }

    return 0;
}