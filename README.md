# Dining Philosophers Problem in C
This is a C implementation of the classic Dining Philosophers problem, featuring a solution that is deadlock-free and starvation-free.
This solution uses a waiter (a semaphore) to prevent deadlock. The waiter allows a maximum of four out of the five philosophers to attempt to eat at the same time. This strategy ensures that the system cannot enter a circular wait state (deadlock) and helps prevent any single philosopher from being indefinitely denied resources (starvation).
