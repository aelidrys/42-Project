- ## Functions used in the program.
    ```c
    0x08048338  _init
    0x08048380  printf
    0x08048390  puts
    0x080483a0  system
    0x080483b0  __gmon_start__
    0x080483c0  __libc_start_main
    0x080483d0  __isoc99_scanf
    0x080483e0  _start
    0x08048410  __do_global_dtors_aux
    0x08048470  frame_dummy
    0x08048494  main
    0x08048520  __libc_csu_init
    0x08048590  __libc_csu_fini
    0x08048592  __i686.get_pc_thunk.bx
    0x080485a0  __do_global_ctors_aux
    0x080485cc  _fini
    ```

- ## Assembly of main function.
    ```c
    0x08048494 <+0>:     push   %ebp
    0x08048495 <+1>:     mov    %esp,%ebp
    0x08048497 <+3>:     and    $0xfffffff0,%esp
    0x0804849a <+6>:     sub    $0x20,%esp
    0x0804849d <+9>:     movl   $0x80485f0,(%esp)
    0x080484a4 <+16>:    call   0x8048390 <puts@plt>
    0x080484a9 <+21>:    movl   $0x8048614,(%esp)
    0x080484b0 <+28>:    call   0x8048390 <puts@plt>
    0x080484b5 <+33>:    movl   $0x80485f0,(%esp)
    0x080484bc <+40>:    call   0x8048390 <puts@plt>
    0x080484c1 <+45>:    mov    $0x804862c,%eax
    0x080484c6 <+50>:    mov    %eax,(%esp)
    0x080484c9 <+53>:    call   0x8048380 <printf@plt>
    0x080484ce <+58>:    mov    $0x8048636,%eax
    0x080484d3 <+63>:    lea    0x1c(%esp),%edx
    0x080484d7 <+67>:    mov    %edx,0x4(%esp)
    0x080484db <+71>:    mov    %eax,(%esp)
    0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt>
    0x080484e3 <+79>:    mov    0x1c(%esp),%eax
    0x080484e7 <+83>:    cmp    $0x149c,%eax
    0x080484ec <+88>:    jne    0x804850d <main+121>
    0x080484ee <+90>:    movl   $0x8048639,(%esp)
    0x080484f5 <+97>:    call   0x8048390 <puts@plt>
    0x080484fa <+102>:   movl   $0x8048649,(%esp)
    0x08048501 <+109>:   call   0x80483a0 <system@plt>
    0x08048506 <+114>:   mov    $0x0,%eax
    0x0804850b <+119>:   jmp    0x804851e <main+138>
    0x0804850d <+121>:   movl   $0x8048651,(%esp)
    0x08048514 <+128>:   call   0x8048390 <puts@plt>
    0x08048519 <+133>:   mov    $0x1,%eax
    0x0804851e <+138>:   leave  
    0x0804851f <+139>:   ret    
    ```
    #### `main` calls `puts` three times with some addresses lets see what it put bellow.
    ```c
    0x0804849d <+9>:     movl   $0x80485f0,(%esp)
    0x080484a4 <+16>:    call   0x8048390 <puts@plt>
    0x080484a9 <+21>:    movl   $0x8048614,(%esp)
    0x080484b0 <+28>:    call   0x8048390 <puts@plt>
    0x080484b5 <+33>:    movl   $0x80485f0,(%esp)
    0x080484bc <+40>:    call   0x8048390 <puts@plt>
    ...
    (gdb) x/s 0x80485f0
    0x80485f0:       '*' <repeats 35 times>
    (gdb) x/s 0x8048614
    0x8048614:       "* \t     -Level00 -\t\t  *"
    (gdb) x/s 0x80485f0
    0x80485f0:       '*' <repeats 35 times>
    ```
    #### As we see it puts just some strings, lets run the program.
    ```c
    (gdb) r
    Starting program: /home/users/level00/level00 
    ***********************************
    *            -Level00 -           *
    ***********************************
    Password:
    ```
    #### After puting the three strings it ask for a password.

    #### By look at the assembly we see that `main` call `scanf`.
    ```c
    0x080484ce <+58>:    mov    $0x8048636,%eax
    0x080484d3 <+63>:    lea    0x1c(%esp),%edx
    0x080484d7 <+67>:    mov    %edx,0x4(%esp)
    0x080484db <+71>:    mov    %eax,(%esp)
    0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt>
    ```
    #### `main` passes `"%d"` and a variable located at `(%esp)+1c`, so it expect a number then the number stored in `(%esp)+1c`.
    ```c
    0x080484e3 <+79>:    mov    0x1c(%esp),%eax
    0x080484e7 <+83>:    cmp    $0x149c,%eax
    0x080484ec <+88>:    jne    0x804850d <main+121>
    ...
    (gdb) x/s 0x8048636
    0x8048636:       "%d"
    ```
    #### This number compared with `0x149c` (`5276` in decimal).
- ## Source code.
    ```c
    #include<stdio.h>
    #include<stdlib.h>

    int main(){
        puts("***********************************");
        puts("* \t     -Level00 -\t\t  *");
        puts("***********************************");
        int input;
        printf("Password:");
        scanf("%d", &input);
        if (input == 5276){
            puts("\nAuthenticated!");
            system("/bin/sh");
            return 0;
        }
        else {
            puts("\nInvalid Password!");
            return 1;
        }
    }
    ```