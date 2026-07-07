#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{

    int value = atoi(argv[1]);

    if (value == 0x1a7) {
        char *path = strdup("/bin/sh");
        char *exec_args[2];

        if (path == NULL) {
            return 1;
        }

        exec_args[0] = path;
        exec_args[1] = NULL;

        gid_t egid = getegid();
        uid_t euid = geteuid();
        setresgid(egid, egid, egid);
        setresuid(euid, euid, euid);

        execv(path, exec_args);
        free(path);
        return 1;
    }
    return 0;
}