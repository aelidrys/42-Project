
# Steps
---
- ## Functions used in this program.
    ```c
    0x0804843c  _init
    0x08048480  printf
    0x08048490  fflush
    0x080484a0  getchar
    0x080484b0  time
    0x080484c0  __stack_chk_fail
    0x080484d0  puts
    0x080484e0  system
    0x080484f0  __gmon_start__
    0x08048500  srand
    0x08048510  __libc_start_main
    0x08048520  rand
    0x08048530  __isoc99_scanf
    0x08048540  _start
    0x08048570  __do_global_dtors_aux
    0x080485d0  frame_dummy
    0x080485f4  clear_stdin
    0x08048617  get_unum
    0x0804864f  prog_timeout
    0x08048660  decrypt
    0x08048747  test
    0x0804885a  main
    0x080488f0  __libc_csu_init
    0x08048960  __libc_csu_fini
    0x08048962  __i686.get_pc_thunk.bx
    0x08048970  __do_global_ctors_aux
    0x0804899c  _fini
    ```

- ### Source code.
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    void decrypt(int key);
    void test(int a, int b);

    int main(void)
    {
        int num;

        srand(time(0));

        puts("***********************************");
        puts("*\t\tlevel03\t\t**");
        puts("***********************************");
        printf("Password:");
        scanf("%d", &num);

        test(num, 322424845);

        return 0;
    }
    ```
    #### `main` use scanf to get the password from user unput aas integer.

    #### After it call `test` function and passes to it the input number and other number `322424845`.

    ```c
    void test(int a, int b)
    {
        int key = b - a;

        switch ((unsigned int)key) {
            case 0:  case 1:  case 2:  case 3:
            case 4:  case 5:  case 6:  case 7:
            case 8:  case 9:  case 10: case 11:
            case 12: case 13: case 14: case 15:
            case 16: case 17: case 18: case 19:
            case 20: case 21:
                decrypt(key);
                break;
            default:
                decrypt(rand());
        }
    }
    ```
    #### `test` substruct its first (our input) parmeter from the second (`322424845`), store the result into `key`.

    #### Next its use a switch cases, that tell the program to call `decrypt` with `key` as a parameter if `key` value between `(0,21)` otherwise it will pass a random value to `decrypt`.

    ```c
    void decrypt(int key)
    {
        char enc[17] = "Q}|u`sfg~sf{}|a3";
        enc[16] = '\0';
        size_t len = strlen(enc);
        size_t i;

        for (i = 0; i < len; i++)
            enc[i] ^= (char)key;

        if (strcmp(enc, "Congratulations!") == 0)
            system("/bin/sh");
        else
            puts("\nInvalid Password");
    }
    ```

    #### `decrypt` initialize the `enc` buffer by a encrypted string "Q}|u`sfg~sf{}|a3".

    #### Then it use `XOR` operation, between each character form `enc` and given parameter `key` but as char `enc[i] ^= (char)key;` so it will use just the lowest 8 bit of the parameter `key`, this operation will change all the characters of `enc` buffer.

    #### After it check if the new values of `enc` buffer equal to `Congratulations!`, sience both of `enc` buffer and this string (`Congratulations!`) have the same size, so the `XOR` operation try to get `Congratulations!` from the first value of `enc` that mean that there is spesific number if we use it we can get `Congratulations!` from this string "Q}|u`sfg~sf{}|a3".

    #### `XOR` is a bitwise operation, it compares two bits and the result is 1 if the bits are different, and 0 if they're the same.

    ```c
    bin1 = 101100101
    bin2 = 111000111
    res  = 010100010
    ```

    #### Detirmin the valid number to convert from "Q}|u`sfg~sf{}|a3" to "Congratulations!", begin by the first characters 'Q' and 'C' and see wish number can convert from 'Q' to 'C'.

    #### The decimal 'Q' is `81` and the decimal of 'C' is `67`.
    ```c
    81 => 1010001
    x  => 0010010 => 18
    67 => 1000011
    ```

    #### The number thatcan convert form 'Q' to 'C' is `18`, but we can't input `18` as password because inside `test` the used number is not the input but `322424845` - input so this substruction result shoud be `18`
    ```c
    322424845 - input = 18
    input = 322424845 - 18 = 322424827
    ```

- ### Solution.
    ```sh
    level03@OverRide:~$ ./level03 
    ***********************************
    *               level03         **
    ***********************************
    Password:322424827
    $ whoami
    level04
    $ cat /home/users/level04/.pass
    kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
    $ 
    ```