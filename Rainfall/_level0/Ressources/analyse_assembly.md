## Get used functions
```c
    0x080481a0  _init
    0x080482e0  group_number
    0x080483b7  _i18n_number_rewrite
    0x08048587  _i18n_number_rewrite
    0x08048757  is_trusted_path_normalize
    0x0804882d  print_search_path
    0x0804897a  strip
    0x080489e6  group_number
    0x08048a90  _i18n_number_rewrite
    0x08048ba0  fini
    0x08048bc0  init_cacheinfo
    0x08048de8  _start
    0x08048e10  __do_global_dtors_aux
    0x08048e80  frame_dummy
    0x08048ec0  main
```
## Assembly of main function
```c
    0x08048ec0 <+0>:     push   %ebp
    0x08048ec1 <+1>:     mov    %esp,%ebp
    0x08048ec3 <+3>:     and    $0xfffffff0,%esp
    0x08048ec6 <+6>:     sub    $0x20,%esp
    0x08048ec9 <+9>:     mov    0xc(%ebp),%eax
    0x08048ecc <+12>:    add    $0x4,%eax
    0x08048ecf <+15>:    mov    (%eax),%eax
    0x08048ed1 <+17>:    mov    %eax,(%esp)
    0x08048ed4 <+20>:    call   0x8049710 <atoi>
    0x08048ed9 <+25>:    cmp    $0x1a7,%eax
    0x08048ede <+30>:    jne    0x8048f58 <main+152>
    0x08048ee0 <+32>:    movl   $0x80c5348,(%esp)
    0x08048ee7 <+39>:    call   0x8050bf0 <strdup>
    0x08048eec <+44>:    mov    %eax,0x10(%esp)
    0x08048ef0 <+48>:    movl   $0x0,0x14(%esp)
    0x08048ef8 <+56>:    call   0x8054680 <getegid>
    0x08048efd <+61>:    mov    %eax,0x1c(%esp)
    0x08048f01 <+65>:    call   0x8054670 <geteuid>
    0x08048f06 <+70>:    mov    %eax,0x18(%esp)
    0x08048f0a <+74>:    mov    0x1c(%esp),%eax
    0x08048f0e <+78>:    mov    %eax,0x8(%esp)
    0x08048f12 <+82>:    mov    0x1c(%esp),%eax
    0x08048f16 <+86>:    mov    %eax,0x4(%esp)
    0x08048f1a <+90>:    mov    0x1c(%esp),%eax
    0x08048f1e <+94>:    mov    %eax,(%esp)
    0x08048f21 <+97>:    call   0x8054700 <setresgid>
    0x08048f26 <+102>:   mov    0x18(%esp),%eax
    0x08048f2a <+106>:   mov    %eax,0x8(%esp)
    0x08048f2e <+110>:   mov    0x18(%esp),%eax
    0x08048f32 <+114>:   mov    %eax,0x4(%esp)
    0x08048f36 <+118>:   mov    0x18(%esp),%eax
    0x08048f3a <+122>:   mov    %eax,(%esp)
    0x08048f3d <+125>:   call   0x8054690 <setresuid>
    0x08048f42 <+130>:   lea    0x10(%esp),%eax
    0x08048f46 <+134>:   mov    %eax,0x4(%esp)
    0x08048f4a <+138>:   movl   $0x80c5348,(%esp)
    0x08048f51 <+145>:   call   0x8054640 <execv>
    0x08048f56 <+150>:   jmp    0x8048f80 <main+192>
    0x08048f58 <+152>:   mov    0x80ee170,%eax
    0x08048f5d <+157>:   mov    %eax,%edx
    0x08048f5f <+159>:   mov    $0x80c5350,%eax
    0x08048f64 <+164>:   mov    %edx,0xc(%esp)
    0x08048f68 <+168>:   movl   $0x5,0x8(%esp)
    0x08048f70 <+176>:   movl   $0x1,0x4(%esp)
    0x08048f78 <+184>:   mov    %eax,(%esp)
    0x08048f7b <+187>:   call   0x804a230 <fwrite>
    0x08048f80 <+192>:   mov    $0x0,%eax
    0x08048f85 <+197>:   leave  
    0x08048f86 <+198>:   ret
```
## Tracking instructions
- #### First call atoi function with the argv[1]. 
    ```c
        0x08048ec6 <+6>:     sub    $0x20,%esp
        0x08048ec9 <+9>:     mov    0xc(%ebp),%eax // mov argv to eax.
        0x08048ecc <+12>:    add    $0x4,%eax // add 4 bytes to eax to point on argv+4 (argv[1]).
        0x08048ecf <+15>:    mov    (%eax),%eax // mov the value of argv+4 (string) to eax.
        0x08048ed1 <+17>:    mov    %eax,(%esp) // mov the argv1 to the top of stack.
        0x08048ed4 <+20>:    call   0x8049710 <atoi> // call atoi
    ```
    #### The first arg converted to a number.
- #### Compare this number with 423 (0x1a7).
    ```c
        0x08048ed9 <+25>:    cmp    $0x1a7,%eax // cmpare eax with 423
        0x08048ede <+30>:    jne    0x8048f58 <main+152> // if not equal jmp to (0x8048f58) if equal continue to the next instructions
        0x08048ee0 <+32>:    movl   $0x80c5348,(%esp)
        0x08048ee7 <+39>:    call   0x8050bf0 <strdup>
    ```
    #### If the condition is true the proram will follow the instruction unitil `call execve` function which is take a command let's see what it take exactly.
- #### After passing the condition the important thing is calling `execve` function
    ```c
        0x08048f46 <+134>:   mov    %eax,0x4(%esp)
        0x08048f4a <+138>:   movl   $0x80c5348,(%esp)
        0x08048f51 <+145>:   call   0x8054640 <execv>
    ```
    #### `Execve` take a string locatted in `0x80c5348`.
    ```c
        (gdb) x/s 0x80c5348
        0x80c5348:       "/bin/sh"
    ```
    #### And fortuntly it take the string "/bin/sh" which means opening a shell code so its done.