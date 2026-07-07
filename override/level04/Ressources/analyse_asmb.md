- ## Functions used in this program.
    ```c
    0x0804845c  _init
    0x080484a0  fflush
    0x080484b0  gets
    0x080484c0  getchar
    0x080484d0  signal
    0x080484e0  alarm
    0x080484f0  wait
    0x08048500  puts
    0x08048510  __gmon_start__
    0x08048520  kill
    0x08048520  kill@plt
    0x08048530  __libc_start_main
    0x08048540  prctl
    0x08048550  fork
    0x08048560  __isoc99_scanf
    0x08048570  ptrace
    0x08048580  _start
    0x080485b0  __do_global_dtors_aux
    0x08048610  frame_dummy
    0x08048634  clear_stdin
    0x08048657  get_unum
    0x0804868f  prog_timeout
    0x080486a0  enable_timeout_cons
    0x080486c8  main
    0x08048830  __libc_csu_init
    0x080488a0  __libc_csu_fini
    0x080488a2  __i686.get_pc_thunk.bx
    0x080488b0  __do_global_ctors_aux
    0x080488dc  _fini
    ```

- ## Assembly code of `main`.
    ```c
    0x080486c8 <+0>:     push   %ebp
    0x080486c9 <+1>:     mov    %esp,%ebp
    0x080486cb <+3>:     push   %edi
    0x080486cc <+4>:     push   %ebx
    0x080486cd <+5>:     and    $0xfffffff0,%esp
    0x080486d0 <+8>:     sub    $0xb0,%esp
    0x080486d6 <+14>:    call   0x8048550 <fork@plt>
    0x080486db <+19>:    mov    %eax,0xac(%esp)
    0x080486e2 <+26>:    lea    0x20(%esp),%ebx
    0x080486e6 <+30>:    mov    $0x0,%eax
    0x080486eb <+35>:    mov    $0x20,%edx
    0x080486f0 <+40>:    mov    %ebx,%edi
    0x080486f2 <+42>:    mov    %edx,%ecx
    0x080486f4 <+44>:    rep stos %eax,%es:(%edi)
    0x080486f6 <+46>:    movl   $0x0,0xa8(%esp)
    0x08048701 <+57>:    movl   $0x0,0x1c(%esp)
    0x08048709 <+65>:    cmpl   $0x0,0xac(%esp)
    0x08048711 <+73>:    jne    0x8048769 <main+161>
    0x08048713 <+75>:    movl   $0x1,0x4(%esp)
    0x0804871b <+83>:    movl   $0x1,(%esp)
    0x08048722 <+90>:    call   0x8048540 <prctl@plt>
    0x08048727 <+95>:    movl   $0x0,0xc(%esp)
    0x0804872f <+103>:   movl   $0x0,0x8(%esp)
    0x08048737 <+111>:   movl   $0x0,0x4(%esp)
    0x0804873f <+119>:   movl   $0x0,(%esp)
    0x08048746 <+126>:   call   0x8048570 <ptrace@plt>
    0x0804874b <+131>:   movl   $0x8048903,(%esp)
    0x08048752 <+138>:   call   0x8048500 <puts@plt>
    0x08048757 <+143>:   lea    0x20(%esp),%eax
    0x0804875b <+147>:   mov    %eax,(%esp)
    0x0804875e <+150>:   call   0x80484b0 <gets@plt>
    0x08048763 <+155>:   jmp    0x804881a <main+338>
    0x08048768 <+160>:   nop
    0x08048769 <+161>:   lea    0x1c(%esp),%eax
    0x0804876d <+165>:   mov    %eax,(%esp)
    0x08048770 <+168>:   call   0x80484f0 <wait@plt>
    0x08048775 <+173>:   mov    0x1c(%esp),%eax
    0x08048779 <+177>:   mov    %eax,0xa0(%esp)
    0x08048780 <+184>:   mov    0xa0(%esp),%eax
    0x08048787 <+191>:   and    $0x7f,%eax
    0x0804878a <+194>:   test   %eax,%eax
    0x0804878c <+196>:   je     0x80487ac <main+228>
    0x0804878e <+198>:   mov    0x1c(%esp),%eax
    0x08048792 <+202>:   mov    %eax,0xa4(%esp)
    0x08048799 <+209>:   mov    0xa4(%esp),%eax
    0x080487a0 <+216>:   and    $0x7f,%eax
    0x080487a3 <+219>:   add    $0x1,%eax
    0x080487a6 <+222>:   sar    %al
    0x080487a8 <+224>:   test   %al,%al
    0x080487aa <+226>:   jle    0x80487ba <main+242>
    0x080487ac <+228>:   movl   $0x804891d,(%esp)
    0x080487b3 <+235>:   call   0x8048500 <puts@plt>
    0x080487b8 <+240>:   jmp    0x804881a <main+338>
    0x080487ba <+242>:   movl   $0x0,0xc(%esp)
    0x080487c2 <+250>:   movl   $0x2c,0x8(%esp)
    0x080487ca <+258>:   mov    0xac(%esp),%eax
    0x080487d1 <+265>:   mov    %eax,0x4(%esp)
    0x080487d5 <+269>:   movl   $0x3,(%esp)
    0x080487dc <+276>:   call   0x8048570 <ptrace@plt>
    0x080487e1 <+281>:   mov    %eax,0xa8(%esp)
    0x080487e8 <+288>:   cmpl   $0xb,0xa8(%esp)
    0x080487f0 <+296>:   jne    0x8048768 <main+160>
    0x080487f6 <+302>:   movl   $0x8048931,(%esp)
    0x080487fd <+309>:   call   0x8048500 <puts@plt>
    0x08048802 <+314>:   movl   $0x9,0x4(%esp)
    0x0804880a <+322>:   mov    0xac(%esp),%eax
    0x08048811 <+329>:   mov    %eax,(%esp)
    0x08048814 <+332>:   call   0x8048520 <kill@plt>
    0x08048819 <+337>:   nop
    0x0804881a <+338>:   mov    $0x0,%eax
    0x0804881f <+343>:   lea    -0x8(%ebp),%esp
    0x08048822 <+346>:   pop    %ebx
    0x08048823 <+347>:   pop    %edi
    0x08048824 <+348>:   pop    %ebp
    0x08048825 <+349>:   ret  
    ```
- ## Source code.
    ```c
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <sys/ptrace.h>
    #include <sys/prctl.h>
    #include <signal.h>

    #define SYS_execve 11   // x86 syscall number for execve

    int main(void)
    {
        int   pid;
        int   status      = 0;
        long  ptrace_data = 0;
        char  buf[128];     // esp+0x20, zeroed by rep stos (32 dwords = 128 bytes)

        pid = fork();

        if (pid == 0) {
            // ---- child ---- 
            prctl(PR_SET_PDEATHSIG, SIGHUP);   // prctl(1, 1) — die if parent dies 
            ptrace(PTRACE_TRACEME, 0, 0, 0);   // request to be traced by parent

            puts("Give me some shellcode, k");
            gets(buf);                          // VULNERABLE: unbounded read into 128-byte buf 
        }
        else {
            // ---- parent (tracer) ---- 
            for (;;) {
                wait(&status);

                if (WIFEXITED(status)) {
                    puts("child is exiting...");
                    break;
                }

                if (!WIFSIGNALED(status)) {
                    // child is stopped (e.g. SIGTRAP from an exec attempt) 
                    ptrace_data = ptrace(PTRACE_PEEKUSER, pid, 0x2c, 0);
                    // offset 0x2c in struct user_regs_struct = orig_eax,
                    //    i.e. the syscall number the child is currently entering 

                    if (ptrace_data == SYS_execve) {
                        puts("no exec() for you");
                        kill(pid, SIGKILL);
                        break;
                    }
                    // otherwise loop back and wait again 
                    continue;
                }

                // child was signaled (not stopped, not exited) 
                puts("child is exiting...");
                break;
            }
        }

        return 0;
    }
    ```