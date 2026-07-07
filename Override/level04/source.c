#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/user.h>

int main(void) {
    pid_t pid;
    int status = 0;
    long syscall_num = 0;
    char buf[128]; 

    pid = fork();
    
    // rep stos %eax,%es:(%edi) with 32 dwords (128 bytes)
    memset(buf, 0, sizeof(buf)); 

    if (pid == 0) {
        // ---------------- CHILD PROCESS ----------------

        // prctl(1, 1) -> PR_SET_PDEATHSIG, SIGHUP
        // Ensures child dies if the parent is killed
        prctl(PR_SET_PDEATHSIG, SIGHUP); 

        // ptrace(0, 0, 0, 0) -> PTRACE_TRACEME
        // Allows the parent process to trace/debug it
        ptrace(PTRACE_TRACEME, 0, NULL, NULL); 

        puts("Give me some shellcode, k");
        
        // The core vulnerability: Unbounded input into a 128-byte buffer
        gets(buf); 
        
        return 0;
        
    } else {
        // ---------------- PARENT PROCESS ----------------
        
        while (1) {
            wait(&status);

            // Assembly macro expansion for WIFEXITED(status) and WIFSIGNALED(status)
            // Checks if the child exited normally or was killed.
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                puts("child is exiting...");
                break;
            }

            // If the child is stopped (e.g., about to execute a syscall), inspect it.
            // PTRACE_PEEKUSER = 3. 
            // 44 is the byte offset for `orig_eax` in x86's user_regs_struct.
            // `orig_eax` holds the system call number the child is attempting to run.
            syscall_num = ptrace(PTRACE_PEEKUSER, pid, 44, NULL);

            // 11 is the syscall number for SYS_execve on 32-bit x86 Linux
            if (syscall_num == 11) {
                puts("no exec() for you");
                kill(pid, SIGKILL); // SIGKILL = 9
                break;
            }
        }
    }

    return 0;
}