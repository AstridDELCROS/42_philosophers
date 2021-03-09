## Philosophers

*Summary: In this project, you will learn the basics of threading a process and how to work on the same memory space. You will learn how to make threads. You will discover the mutex, semaphore and shared memory.*

**Mandatory part**

You will have to write 3 different programs but they will have the same basic rules:

- This project is to be coded in C, following the Norm. Any leak, crash, undefined behavior or norm error means 0 to the project.
- A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping.
- While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.
- As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
- The philosophers must never be starving.
- Every philosopher needs to eat.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- Each time a philosopher has finishedeating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.
- Each program should have the same options: number\_of\_philosophers time\_to\_die time\_to\_eat time\_to\_sleep [number\_of\_times\_each\_philosopher\_must\_eat]
- number\_of\_philosophers: is the number of philosophers and also the number of forks
- time\_to\_die: is in milliseconds, if a philosopher doesn’t start eating ’time\_to\_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
- time\_to\_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
- time\_to\_sleep: is in milliseconds and is the time the philosopher will spend sleeping.
- number\_of\_times\_each\_philosopher\_must\_eat: argument is optional, if all philosophers eat at least ’number\_of\_times\_each\_philosopher\_must\_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
- Each philosopher should be given a number from 1 to ’number\_of\_philosophers’.
- Philosopher number 1 is next to philosopher number ’number\_of\_philosophers’. Any other philosopher with number N is seated between philosopher N - 1 and philosopher N + 1
- Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp\_in\_ms the current timestamp in milliseconds)
- timestamp\_in\_ms X has taken a fork
- timestamp\_in\_ms X is eating
- timestamp\_in\_ms X is sleeping
- timestamp\_in\_ms X is thinking
- timestamp\_in\_ms X died
- The status printed should not be scrambled or intertwined with another philosopher’s status.
- You can’t have more than 10 ms between the death of a philosopher and when it will print its death.
- Again, philosophers should avoid to die!

|**Program name**|philo\_one|
| - | - |
|**Turn in files**|philo\_one/|
|**Makefile**|Yes|
|**Arguments**|number\_of\_philosophers time\_to\_die time\_to\_eat time\_to\_sleep [number\_of\_times\_each\_philosopher\_must\_eat]|
|**External functs.**|<p>memset, printf, malloc, free, write,</p><p>usleep, gettimeofday, pthread\_create, pthread\_detach, pthread\_join, pthread\_mutex\_init, pthread\_mutex\_destroy, pthread\_mutex\_lock, pthread\_mutex\_unlock</p>|
|**Libft authorized**|No|
|**Description**|philosopher with threads and mutex|

In this version the non common rules will be:

- One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a mutex for each of them.
- Each philosopher should be a thread.

|**Program name**|philo\_two|
| - | - |
|**Turn in files**|philo\_two/|
|**Makefile**|Yes|
|**Arguments**|number\_of\_philosophers time\_to\_die time\_to\_eat time\_to\_sleep [number\_of\_times\_each\_philosopher\_must\_eat]|
|**External functs.**|memset, printf, malloc, free, write, usleep, gettimeofday, pthread\_create, pthread\_detach, pthread\_join, sem\_open, sem\_close, sem\_post, sem\_wait, sem\_unlink|
|**Libft authorized**|No|
|**Description**|philosopher with threads and semaphore|

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a thread.

|**Program name**|philo\_three|
| - | - |
|**Turn in files**|philo\_three/|
|**Makefile**|Yes|
|**Arguments**|number\_of\_philosophers time\_to\_die time\_to\_eat time\_to\_sleep [number\_of\_times\_each\_philosopher\_must\_eat]|
|**External functs.**|memset, printf, malloc, free, write, fork, kill, exit, pthread\_create, pthread\_detach, pthread\_join, usleep, gettimeofday, waitpid, sem\_open, sem\_close, sem\_post, sem\_wait, sem\_unlink|
|**Libft authorized**|No|
|**Description**|philosopher with processes and semaphore|

In this version the non common rules will be:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.
