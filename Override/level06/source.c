#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>


int auth(char *login, unsigned int serial);

int main(int argc, char **argv) {
    char login[32];         // Allocated via sub $0x50,%esp and read into 0x2c(%esp)
    unsigned int serial;    // Stored at 0x28(%esp)

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");

    if (fgets(login, 32, stdin) == NULL) {
        return 1;
    }

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    if (scanf("%u", &serial) == -1) {
        return 1;
    }
    if (auth(login, serial) == 0) {
        puts("Authenticated!");
        system("/bin/sh");
        return 0;
    }

    return 1;
}

int auth(char *login, unsigned int serial) {
    login[strcspn(login, "\n")] = '\0';

    int len = strnlen(login, 32);

    if (len <= 5) {
        return 1;
    }
    if (ptrace(0, 0, 1, 0) == -1) {
        puts("\033[32m.---------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !!  |");
        puts("\033[32m'---------------------------'");
        return 1;
    }

    unsigned int hash_val = (login[3] ^ 4919) + 6221293;

    for (int i = 0; i < len; i++) {
        if (login[i] <= 31) {
            return 1;
        }

        unsigned int calculated_mod = (login[i] ^ hash_val) % 1337;
        hash_val += calculated_mod;
    }
    printf("\nhash_val = %u\n", hash_val);
    
    if (serial == hash_val) {
        return 0;
    } else {
        return 1;
    }
}