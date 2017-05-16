# Multi-Threaded-Consumer
This program shows an implementation of multi-threaded programming with synchronization using semaphores

For this assignment, you will implement a multi-threaded producer-consumer program using
a bounded buffer. Use full and empty semaphores to keep track of the numbers of full and
empty slots available to the consumers and producers, respectively. Use a mutex to
coordinate access to the buffer (once the thread determines that there is an available slot via
the appropriate semaphore). The buffer should have 16 slots total. There are 2 producers, 4
consumers, and each producer produces 32 items. The number of producers, the number of
consumers, and the number of items each producer produces should be specified by their
binary log as command-line parameters. Thus, the following command should generate 2
producers, 4 consumers, and 32 items produced by each producer:
./producer-consumer 1 2 5
The consumers need to each consume the same number of items before exiting. Your code
should calculate the number of items each consumer needs to consume so that every item
produced gets consumed. The main thread should parse all of the command-line parameters,
print them in a message, initialize the synchronization objects, spawn all of the threads, wait
for them to complete, and then print a final message. The items produced by the producer
threads should be integers, obtained using the following expression:
thread_number * num_produced + counter
where thread_number is an integer passed to each thread ranging from 0 to num_threads - 1,
num_produced is the number of items produced by each producer, and counter is a local
variable in each thread that gets initialized to 0 and incremented every time a new item is
produced. For example, if each producer produces 32 items, the first item produced by the
producer with thread_number = 0 is (0 * 32 + 0) = 0, the second item produced by this
producer is (0 * 32 + 1) = 1, …, and the last item produced by this producer is (0 * 32 + 31) = 31.
The consumer threads should consume these items by simply printing them. (Printing is the
only required "consumption".)
Use the functions pthread_mutex_init(), pthread_mutex_lock(),
pthread_mutex_unlock(), sem_init(), sem_wait() and sem_post() for 
synchronization in POSIX.