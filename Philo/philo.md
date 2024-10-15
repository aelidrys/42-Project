<div align='center'>
<h1>Philosophers</h1>
<p>in philosophers project we have to solve <a href='https://en.wikipedia.org/wiki/Dining_philosophers_problem'>dining philosophers problem</a></p>
<p> the dining philosophers problem is an example problem often used to get an introduction to <a href="https://en.wikipedia.org/wiki/Concurrent_computing">concurrent programing</a> </p>
</div>

<div align='center'><h2>General idea</h2></div>

- <p>X amount of philosophers sit at a round table with bowls of food.</p>
- <p>Each philosopher have a fork placed in right of it (doesn't really change if they place it on the right or left).</p>
- <p>Number of forks at a table is the same as philosophers.</p>
- <p>Philosopher can do three things: eat, think or sleep.</p>
- <p>A philosopher cannot eat with one fork, so in order to eat he must pick up his fork and the fork on his left.</p>

<h4>the target is to create an algorithm that manage the three activities (eat, sleep, think) for n philosophers in the optimal way that try as mush as can to avoid died of philosophers, with consider the constraints in the <a href='https://cdn.intra.42.fr/pdf/pdf/73397/en.subject.pdf'>subject</a></h4>

lets assume that we have four philosophers sitting at the table.

<img src='philo_01.png' alt='No img' width=500>

philosopher 1 wants to eat, so he take his fork and the fork on his left (fork of philo 2), philosophers 2 and 4 cannot eat because just one fork available for each one of them, philosopher 3 can eat if both of philosophers 2 and 4 don't take any fork

+ case (1) if one of philosophers 2 or 4 take the available fork next to it, they should waiting the philosopher 1 until finish eating, and philosopher 3 should waiting until 2 or 4 finish eating.
+ case (2) if both of philosophers 2 and 4 don't take any fork, and philosopher 3 taking both of forks the right and the left. so the odd set of philosophers (1, 3) eating. and the even set of philosophers (2, 4) waitnig until the odd set of philosophers finish eatinig.

<div align='center'><h2>Resources</h2></div>
<a href='https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2'>Philosophers 42 Guide <span style="color:Tomato;">Medium</span></a>
