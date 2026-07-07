## Functions used in the program.
```c
0x080482f8  _init
0x08048340  printf
0x08048340  printf@plt
0x08048350  fgets
0x08048350  fgets@plt
0x08048360  system
0x08048360  system@plt
0x08048370  __gmon_start__
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  p
0x08048457  n
0x080484a7  main
0x080484c0  __libc_csu_init
0x08048530  __libc_csu_fini
0x08048532  __i686.get_pc_thunk.bx
0x08048540  __do_global_ctors_aux
0x0804856c  _fini
```
## Assembly code of main function.
```c
0x080484a7 <+0>:     push   %ebp
0x080484a8 <+1>:     mov    %esp,%ebp
0x080484aa <+3>:     and    $0xfffffff0,%esp
0x080484ad <+6>:     call   0x8048457 <n>
0x080484b2 <+11>:    leave  
0x080484b3 <+12>:    ret   
```
- #### Main is just call n fiunction.
## Assembly code of n function.
```c
0x08048457 <+0>:     push   %ebp
0x08048458 <+1>:     mov    %esp,%ebp
0x0804845a <+3>:     sub    $0x218,%esp
0x08048460 <+9>:     mov    0x8049804,%eax
0x08048465 <+14>:    mov    %eax,0x8(%esp)
0x08048469 <+18>:    movl   $0x200,0x4(%esp)
0x08048471 <+26>:    lea    -0x208(%ebp),%eax
0x08048477 <+32>:    mov    %eax,(%esp)
0x0804847a <+35>:    call   0x8048350 <fgets@plt>
0x0804847f <+40>:    lea    -0x208(%ebp),%eax
0x08048485 <+46>:    mov    %eax,(%esp)
0x08048488 <+49>:    call   0x8048444 <p>
0x0804848d <+54>:    mov    0x8049810,%eax
0x08048492 <+59>:    cmp    $0x1025544,%eax
0x08048497 <+64>:    jne    0x80484a5 <n+78>
0x08048499 <+66>:    movl   $0x8048590,(%esp)
0x080484a0 <+73>:    call   0x8048360 <system@plt>
0x080484a5 <+78>:    leave  
0x080484a6 <+79>:    ret
```
- #### Function `n` reads from the input and saves it in a buffer, but this time by `fgets`, so there is a size limitation. After that, it calls `p` and passes the buffer to it.
- #### After that, it compares a global variable with the number 16930116 (`0x1025544` in hex). If they are equal, it calls `system`; otherwise, it returns to the `main` function.
    ```c
    (gdb) x/d 0x8049810
    0x8049810 <m>:  0
    (gdb)
    ...
    level4@RainFall:~$ python
    >>> int(0x1025544)
    16930116
    ```
## Assembly code of p function.
```c
0x08048444 <+0>:     push   %ebp
0x08048445 <+1>:     mov    %esp,%ebp
0x08048447 <+3>:     sub    $0x18,%esp
0x0804844a <+6>:     mov    0x8(%ebp),%eax
0x0804844d <+9>:     mov    %eax,(%esp)
0x08048450 <+12>:    call   0x8048340 <printf@plt>
0x08048455 <+17>:    leave  
0x08048456 <+18>:    ret
```
- #### Function p print the buffer that it recieve from n using printf and without any string format this mean that the buffer will considered as string format. so we can enter string formats as input to the program and it will work. so we can read from the stack and we can also write using `%n` format which write the number of the previous printed characters.