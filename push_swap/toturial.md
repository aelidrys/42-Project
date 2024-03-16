# P_S toturial
## simple explanation of chunks algorithm in push swap
- [X] ___first part contain three staeps___  
- [ ] ___second part contain one steap___
- ### 1 ranking the elements of stack `a` `figure 2`
- ### 2 specifying the `stack_size` & `midlle` of stack `a` and the `start` & `end` & `set` of chunk `figure 3`
- ### 3 searching about the elements of chunk and push each elements of chunk to stack `b` when the `chunk_size` = 0 expand chunk and repet this process `figure 4,...,12`

#### create stack `a` and represent it by a linked list data structur
![x](images/img1.png)
#### ranking the elements of stack `a`
![x](images/img2.png)
#### set `stack_size` & `midlle` & `start` & `end` & `set`, varible `set` represent the chunk
![x](images/img3.png)
#### if the element to be pushed is at the top of `a`, push it otherwise use `ra` until it is at the top
![x](images/img4.png)
#### the same thing as the previos figure
![x](images/img5.png)
#### the same thing as the previos figure
![x](images/img6.png)
#### after pushing a element check if the order of this element is lower than the `midlle` if it lower use `rb` this operation make the stack `b` more organized than stack `a` and easily the sorting
![x](images/img7.png)
#### expand chunk
![x](images/img8.png)
#### P_S
![x](images/img9.png)
#### P_S
![x](images/img10.png)
#### P_S
![x](images/img11.png)
#### P_S
![x](images/img12.png)