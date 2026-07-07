## Get used function.
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
## Assembly of main function.
```c
   0x0804853f <+0>:     push   %ebp
   0x08048540 <+1>:     mov    %esp,%ebp
   0x08048542 <+3>:     and    $0xfffffff0,%esp
   0x08048545 <+6>:     call   0x80484d4 <p>
   0x0804854a <+11>:    leave  
   0x0804854b <+12>:    ret
```
- #### Main just call p
## Assembly of p function.
```c
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
## Address of system function.
```c
   (gdb) x/s 0x8048620
   0x8048620:       "(%p)\n"
```
## Address of string "/bin/sh" in libc.
```c
(gdb) info proc map
process 2695
Mapped address spaces:

      Start Addr   End Addr       Size     Offset objfile
      0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
      0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
      0xb7e2b000 0xb7e2c000     0x1000        0x0 
      0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
      0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
      0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
      0xb7fd2000 0xb7fd5000     0x3000        0x0 
      0xb7fda000 0xb7fdd000     0x3000        0x0 
      0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
      0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
      0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
      0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
      0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) find 0xb7e2c000, +99999999, "/bin/sh"
0xb7f8cc58
1 pattern found.
(gdb)
```