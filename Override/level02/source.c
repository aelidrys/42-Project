#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *fp;
    int  n;
    char buf1[100];   /* "Username" input from user */
    char buf2[41];    /* password loaded from file  */
    char buf3[100];   /* password entered by user   */

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(buf3, 0, sizeof(buf3));

    fp = fopen("/home/users/level03/.pass", "r");
    if (fp == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
        exit(1);
    }

    n = fread(buf2, 1, 0x29, fp);
    buf2[strcspn(buf2, "\n")] = '\0';

    if (n != 0x29) {
        fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
        exit(1);
    }

    fclose(fp);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\***************************************/");

    printf("--[ Username: ");
    fgets(buf1, 100, stdin);
    buf1[strcspn(buf1, "\n")] = '\0';

    printf("--[ Password: ");
    fgets(buf3, 100, stdin);
    buf3[strcspn(buf3, "\n")] = '\0';

    puts("*****************************************");

    if (strncmp(buf2, buf3, 0x29) == 0) {
        printf("Greetings, %s!\n", buf1);
        system("/bin/sh");
        return 0;
    } else {
        printf(buf1);
        puts(" does not have access!");
        exit(1);
    }
}