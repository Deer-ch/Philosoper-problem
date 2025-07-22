# Dining Philosophers Problem in C
This is a C implementation of the classic Dining Philosophers synchronization problem.
This solution uses a waiter (a semaphore) to prevent deadlock. The waiter allows a maximum of four out of the five philosophers to attempt to eat at the same time, which guarantees that at least one philosopher can always acquire both chopsticks.
