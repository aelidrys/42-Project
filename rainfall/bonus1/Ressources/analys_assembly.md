- #### Get used functions.
    ```c
        0x080482d4  _init
        0x08048320  memcpy
        0x08048330  __gmon_start__
        0x08048340  __libc_start_main
        0x08048350  execl
        0x08048360  atoi
        0x08048370  _start
        0x080483a0  __do_global_dtors_aux
        0x08048400  frame_dummy
        0x08048424  main
        0x080484b0  __libc_csu_init
        0x08048520  __libc_csu_fini
        0x08048522  __i686.get_pc_thunk.bx
        0x08048530  __do_global_ctors_aux
        0x0804855c  _fini
    ```
- #### Assembly of main.
    ```c
        0x08048424 <+0>:     push   %ebp
        0x08048425 <+1>:     mov    %esp,%ebp
        0x08048427 <+3>:     and    $0xfffffff0,%esp
        0x0804842a <+6>:     sub    $0x40,%esp
        0x0804842d <+9>:     mov    0xc(%ebp),%eax
        0x08048430 <+12>:    add    $0x4,%eax
        0x08048433 <+15>:    mov    (%eax),%eax
        0x08048435 <+17>:    mov    %eax,(%esp)
        0x08048438 <+20>:    call   0x8048360 <atoi@plt>
        0x0804843d <+25>:    mov    %eax,0x3c(%esp)
        0x08048441 <+29>:    cmpl   $0x9,0x3c(%esp)
        0x08048446 <+34>:    jle    0x804844f <main+43>
        0x08048448 <+36>:    mov    $0x1,%eax
        0x0804844d <+41>:    jmp    0x80484a3 <main+127>
        0x0804844f <+43>:    mov    0x3c(%esp),%eax
        0x08048453 <+47>:    lea    0x0(,%eax,4),%ecx
        0x0804845a <+54>:    mov    0xc(%ebp),%eax
        0x0804845d <+57>:    add    $0x8,%eax
        0x08048460 <+60>:    mov    (%eax),%eax
        0x08048462 <+62>:    mov    %eax,%edx
        0x08048464 <+64>:    lea    0x14(%esp),%eax <-
        0x08048468 <+68>:    mov    %ecx,0x8(%esp)
        0x0804846c <+72>:    mov    %edx,0x4(%esp)
        0x08048470 <+76>:    mov    %eax,(%esp)
        0x08048473 <+79>:    call   0x8048320 <memcpy@plt>
        0x08048478 <+84>:    cmpl   $0x574f4c46,0x3c(%esp)
        0x08048480 <+92>:    jne    0x804849e <main+122>
        0x08048482 <+94>:    movl   $0x0,0x8(%esp)
        0x0804848a <+102>:   movl   $0x8048580,0x4(%esp)
        0x08048492 <+110>:   movl   $0x8048583,(%esp)
        0x08048499 <+117>:   call   0x8048350 <execl@plt>
        0x0804849e <+122>:   mov    $0x0,%eax
        0x080484a3 <+127>:   leave  
        0x080484a4 <+128>:   ret 
    ```
- #### Get the approximated source code.
    ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <unistd.h>

        int main(int ac, char **av) {
            char buffer[40];
            int size;
            size = atoi(av[1]);

            if (size > 9) {
                return 1;
            }

            memcpy(buffer, av[2], size * 4);

            // 0x574f4c46 translated to ASCII text is "FLOW"
            if (size == 0x574f4c46) {
                execl("/bin/sh", "sh", NULL); 
            }

            return 0;
        }

    ```
- #### Math explination.
    ```math
        2^{32} = 4294967296
    ```

    ```math
         \text{Positive Twin} = \frac{4294967296*3+44}{4} = 3221225483   
    ```
    ```math
        3221225483 - 4294967296 = -1073741813
    ```