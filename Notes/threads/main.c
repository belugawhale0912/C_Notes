#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function prototype for the thread routine. 
// Must return 'void *' and accept 'void *' to comply with POSIX thread specifications.
void *process(void *input);

// Prototypes for running single-threaded versus multi-threaded execution benchmarks.
void singleThreadRun();
void multiThreadRun();

int main(){
    // Executing the multi-threaded routine to demonstrate hardware parallelism.
	multiThreadRun();
}

// The core worker function executed concurrently by each thread.
void *process(void *input){

    // Unpacking the generic 'void *' argument back into a scalar 'long' value.
    // (Note: Here we are passing the raw value directly through the pointer slot 
    // rather than pointing to a memory address location).
	long number = (long)input;

    // Heavy computational loop to simulate CPU-bound workload.
	for(int i = 0; i < 1000000000; i ++){
		number += i;
	}

    // Thread routine must return a void * pointer; returning NULL satisfies this requirement.
	return NULL;
}

// Executes thread creation and joining sequentially (one finishes before the next begins).
void singleThreadRun(){
	pthread_t thread1;
	pthread_t thread2;

	long inputA = 0;
	long inputB = 0;

    // Create thread 1 and immediately join/wait for it to terminate completely.
	pthread_create(&thread1, NULL, process, (void*)inputA);
	pthread_join(thread1, NULL);
	
    // Thread 2 only starts *after* thread 1 has fully completed. 
    // This results in sequential (single-threaded execution time).
	pthread_create(&thread2, NULL, process, (void*)inputB);
	pthread_join(thread2, NULL);
}

// Executes thread creation concurrently (both run at the same time on available CPU cores).
void multiThreadRun(){
	pthread_t thread1;
	pthread_t thread2;

	long inputA = 0;
	long inputB = 0;

    // Spawn both threads back-to-back before waiting on either.
    // The OS scheduler maps these software threads to separate hardware CPU threads simultaneously.
	pthread_create(&thread1, NULL, process, (void*)inputA);	
	pthread_create(&thread2, NULL, process, (void*)inputB);

    // Wait for both concurrent worker threads to wrap up execution.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}
