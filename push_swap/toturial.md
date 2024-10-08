# P_S toturial
## simple explanation of chunks algorithm in push swap
##### This algorithm is designed for larger amount of integers. This algorithm splits stack `a` into smaller chunks which are pushed to stack `b`
- [X] ___first part contain three staeps___  
- ### (1) ranking the elements of stack `a` *`figure 2`*, once the numbers is ordered you can use just the order of each number to sort it
- ### (2) specifying the `stack_size` and the `midlle` of stack `a` and the `start` & `end` of chunk, and `set` of elements *`figure 3`*
- ### (3) searching about the elements of chunk and push each elements of chunk to stack `b` when the `chunk_size` = 0 expand chunk and repet this process *`figure 4,...,12`*
---
#### create stack `a` and represent it by a linked list data structur
![x](images1/img1.png)

---
<h4> ranking the elements of stack <span style='color:Orange;'>`a`</span>, the rank of each number is represented by the red color in side it</h4>

<img src='images1/img2.png'></img>

---
#### initialize `stack_size` & `midlle` & `start` & `end` & `set`, varible `set` represent the chunk or range, `middle = stack_size/2`, `start = midddle - range_size/2`, `end = midddle + range_size/2`, `range_size` of your choise ofcourse you should choose a `range_size` that give the best result. for example in a `set` that containe a number of element between 20 >= num_of_elem <= 100 i choose 32 as a `range_size`
![x](images1/img3.png)

---
#### if the element to be pushed is at the top of `a`, push it otherwise use `ra` until it is at the top
![x](images1/img4.png)

---
#### the same thing as the previos figure
![x](images1/img5.png)

---
#### the same thing as the previos figure
![x](images1/img6.png)

---
#### after pushing each element check if the order of this element is lower than the `midlle` if it lower use `rb` this operation make the stack `b` more organized than stack `a` and easily the sorting
![x](images1/img7.png)

---
#### expand chunk update `start` and `end` of chunk and add new numbers to (chunk) `set`
![x](images1/img8.png)

---
#### P_S
![x](images1/img9.png)

---
#### P_S
![x](images1/img10.png)

---
#### P_S
![x](images1/img11.png)

---
#### P_S
![x](images1/img12.png)

---
- [x] ___second part contain tow steaps___
- ### (1) specify the number that have the max order and push it to stack `a` `figure 2`, this steap is mandatory
- ### (2) complete the pushing of remaining numbers to stack `a` with follow one of the following conditions `figures [3,...,12]`
    - #### cond1: if the `max_order` in the top of stack `b` push it to stack `a`
    - #### cond2: if cond1 is False and the `max_order` existe in the last of `a` use `rra` to move it to the top of stack `a`
    - #### cond3: if both of cond1 and cond2 is False and the element that existe in the top of `b` lower than the element that in the last of stack `a` push it to stack `a` and rotate it by useing `pa` + `ra`
    - #### (4) if all of the previos conditions is False,  make the `max_order` in the top and push it to stack `a` there is tow way to make it in the top `rb` or `rrb` you should choise the way that give the least number of instructions
---
#### specify the `max_order` the `max_order` is the order of the larger number that has not taken its correct position, in first it will be the `stack_size`, once the larger number take the correct position `max_order` will decrement to be the order of the next larger number
#### `InLastOf_a` represent the number of elements in stack `a` bellow of the first `max_order` in this example the first `max_order` is 8 and `ILO_a` is the set of numbers that existe bellow of order 8
![x](images2/img1.png)

---
#### search about the max number and push it to `a`
![x](images2/img2.png)

---
#### cond3 has been achieved
![x](images2/img3.png)

---
#### no condition from the three conditions has been achieved, case (4) the choised way is `rrb`
![x](images2/img4.png)

---
#### no condition from the three conditions has been achieved, case (4) the choised way is `rb`
![x](images2/img5.png)

---
#### cond2 has been achieved
![x](images2/img6.png)

---
#### cond3 has been achieved
![x](images2/img7.png)

---
#### no condition from the three conditions has been achieved, case (4) the choised way is `rrb`
![x](images2/img8.png)

---
#### cond2 has been achieved
![x](images2/img9.png)


---
#### cond1 has been achieved
![x](images2/img10.png)

---
#### cond1 has been achieved
![x](images2/img11.png)

---
### No more
![x](images2/img12.png)
