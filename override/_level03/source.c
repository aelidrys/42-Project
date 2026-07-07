#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void decrypt(int key);
void test(int a, int b);

int main(void)
{
    int num;

    srand(time(0));

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &num);

    test(num, 322424845);

    return 0;
}

void test(int a, int b)
{
    int idx = b - a;

    switch ((unsigned int)idx) {
        case 0:  case 1:  case 2:  case 3:
        case 4:  case 5:  case 6:  case 7:
        case 8:  case 9:  case 10: case 11:
        case 12: case 13: case 14: case 15:
        case 16: case 17: case 18: case 19:
        case 20: case 21:
            decrypt(idx);
            break;
        default:
            decrypt(rand());
    }
}

void decrypt(int key)
{
    char enc[17] = "Q}|u`sfg~sf{}|a3";
    enc[16] = '\0';
    size_t len = strlen(enc);
    size_t i;

    for (i = 0; i < len; i++)
        enc[i] ^= (char)key;

    if (strcmp(enc, "Congratulations!") == 0)
        system("/bin/sh");
    else
        puts("\nInvalid Password");
}



