## Used functions in this program.
```c
0x080482f4  _init
0x08048340  strcpy
0x08048340  strcpy@plt
0x08048350  malloc
0x08048350  malloc@plt
0x08048360  puts
0x08048360  puts@plt
0x08048370  system
0x08048370  system@plt
0x08048380  __gmon_start__
0x08048380  __gmon_start__@plt
0x08048390  __libc_start_main
0x08048390  __libc_start_main@plt
0x080483a0  _start
0x080483d0  __do_global_dtors_aux
0x08048430  frame_dummy
0x08048454  n
0x08048468  m
0x0804847c  main
0x080484e0  __libc_csu_init
0x08048550  __libc_csu_fini
0x08048552  __i686.get_pc_thunk.bx
0x08048560  __do_global_ctors_aux
0x0804858c  _fini
```
## Assembly of main function
```c
0x0804847c <+0>:     push   %ebp
0x0804847d <+1>:     mov    %esp,%ebp
0x0804847f <+3>:     and    $0xfffffff0,%esp
0x08048482 <+6>:     sub    $0x20,%esp
0x08048485 <+9>:     movl   $0x40,(%esp)
0x0804848c <+16>:    call   0x8048350 <malloc@plt>
0x08048491 <+21>:    mov    %eax,0x1c(%esp)
0x08048495 <+25>:    movl   $0x4,(%esp)
0x0804849c <+32>:    call   0x8048350 <malloc@plt>
0x080484a1 <+37>:    mov    %eax,0x18(%esp)
0x080484a5 <+41>:    mov    $0x8048468,%edx
0x080484aa <+46>:    mov    0x18(%esp),%eax
0x080484ae <+50>:    mov    %edx,(%eax)
0x080484b0 <+52>:    mov    0xc(%ebp),%eax
0x080484b3 <+55>:    add    $0x4,%eax
0x080484b6 <+58>:    mov    (%eax),%eax
0x080484b8 <+60>:    mov    %eax,%edx
0x080484ba <+62>:    mov    0x1c(%esp),%eax
0x080484be <+66>:    mov    %edx,0x4(%esp)
0x080484c2 <+70>:    mov    %eax,(%esp)
0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
0x080484ca <+78>:    mov    0x18(%esp),%eax
0x080484ce <+82>:    mov    (%eax),%eax
0x080484d0 <+84>:    call   *%eax
0x080484d2 <+86>:    leave  
0x080484d3 <+87>:    ret 
```
- #### `main` uses `malloc` with `0x40` <=> `64` in decimal, and it uses `malloc` again with `4` bytes this time. It then moves an address into the second location, as shown below.
    ```c
    0x0804849c <+32>:    call   0x8048350 <malloc@plt>
    0x080484a1 <+37>:    mov    %eax,0x18(%esp)
    0x080484a5 <+41>:    mov    $0x8048468,%edx
    0x080484aa <+46>:    mov    0x18(%esp),%eax
    0x080484ae <+50>:    mov    %edx,(%eax)
    ```
    #### Use gdb to discover the address information.
    ```c
    (gdb) disas 0x8048468
    Dump of assembler code for function m:
    0x08048468 <+0>:     push   %ebp
    0x08048469 <+1>:     mov    %esp,%ebp
    0x0804846b <+3>:     sub    $0x18,%esp
    0x0804846e <+6>:     movl   $0x80485d1,(%esp)
    0x08048475 <+13>:    call   0x8048360 <puts@plt>
    0x0804847a <+18>:    leave  
    0x0804847b <+19>:    ret    
    End of assembler dump.
    (gdb)
    ```
    #### Its the address of function `m`.
- #### The it call `strcpy` and passes to it the first allocated `buffer` and `argv[1]`.
    ```c
    0x08048485 <+9>:     movl   $0x40,(%esp)
    0x0804848c <+16>:    call   0x8048350 <malloc@plt>
    0x08048491 <+21>:    mov    %eax,0x1c(%esp) // the address of the allocated bytes saved here.
    ...
    0x080484b0 <+52>:    mov    0xc(%ebp),%eax // mov argv to eax.
    0x080484b3 <+55>:    add    $0x4,%eax // add 4 bytes to argv means point to argv[1].
    0x080484b6 <+58>:    mov    (%eax),%eax // mov the value of argv[1] to eax.
    0x080484b8 <+60>:    mov    %eax,%edx
    0x080484ba <+62>:    mov    0x1c(%esp),%eax // mov the allocated buffer to eax
    0x080484be <+66>:    mov    %edx,0x4(%esp) // mov argv[1] to esp+4
    0x080484c2 <+70>:    mov    %eax,(%esp) // mov buffer to esp
    0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
    ```
    #### Call m as bellow.
    ```c
    0x08048495 <+25>:    movl   $0x4,(%esp)
    0x0804849c <+32>:    call   0x8048350 <malloc@plt>
    0x080484a1 <+37>:    mov    %eax,0x18(%esp) // mov return of malloc to eax.
    0x080484a5 <+41>:    mov    $0x8048468,%edx // mov address of m to edx
    0x080484aa <+46>:    mov    0x18(%esp),%eax // mov the pointer of the allocated 4 bytes to eax.
    0x080484ae <+50>:    mov    %edx,(%eax) // mov address of m to the allocated 4 butes.
    ...
    0x080484ca <+78>:    mov    0x18(%esp),%eax // mov the pointer of the allocated 4 bytes to eax.
    0x080484ce <+82>:    mov    (%eax),%eax // mov address of m to the eax
    0x080484d0 <+84>:    call   *%eax // call m
    ```

## Assembly of m function
```c
0x08048468 <+0>:     push   %ebp
0x08048469 <+1>:     mov    %esp,%ebp
0x0804846b <+3>:     sub    $0x18,%esp
0x0804846e <+6>:     movl   $0x80485d1,(%esp)
0x08048475 <+13>:    call   0x8048360 <puts@plt>
0x0804847a <+18>:    leave  
0x0804847b <+19>:    ret
```
- #### Function m just puts a string "Nope" as bellow.
    ```c
    (gdb) x/s 0x80485d1
    0x80485d1:       "Nope"
    ```
## Assembly of n function
```c
0x08048454 <+0>:     push   %ebp
0x08048455 <+1>:     mov    %esp,%ebp
0x08048457 <+3>:     sub    $0x18,%esp
0x0804845a <+6>:     movl   $0x80485b0,(%esp)
0x08048461 <+13>:    call   0x8048370 <system@plt>
0x08048466 <+18>:    leave  
0x08048467 <+19>:    ret
```
- #### Function n is the important function because it call `system` with a command in address `0x80485b0`.
    ```c
    (gdb) x/s 0x80485b0
    0x80485b0:       "/bin/cat /home/user/level7/.pass"
    ```