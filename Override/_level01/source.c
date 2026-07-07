#include <stdio.h>
#include <string.h>

char a_user_name[256];

int verify_user_name(void)
{
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass)
{
    return strncmp(pass, "admin", 5);
}


int main(void)
{
    char buf[64];   // esp+0x1c, zeroed by rep stos 
    int  ret;       // esp+0x5c, right after buf[] 

    ret = 0;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");

    fgets(a_user_name, 256, stdin);

    ret = verify_user_name();

    if (ret != 0) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");

    fgets(buf, 100, stdin);     // reads 100 bytes into a 64-byte buf

    ret = verify_user_pass(buf);

    if (ret == 0)
        goto wrong_password;

    if (ret == 0)
        goto correct_password;

    wrong_password:
        puts("nope, incorrect password...\n");
        return 1;

    correct_password:
        return 0;
}
