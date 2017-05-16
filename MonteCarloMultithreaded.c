#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


int insideCircleCount = 0;
int roundsPerThread = 0;
int threadNum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *MonteCarlo(){

	
	int pointsInCircleFromThread = 0;
	unsigned int rand_state = rand();
	int i;
	for(i = 0; i < roundsPerThread; i++){
	
		//rand() is not thread safe

		double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
		
		if( (x*x) + (y*y) < 1){
			pointsInCircleFromThread++;
		}
	}

	//lock global count of pointsInsideCircle

	
	pthread_mutex_lock(&mutex);
	threadNum++;
	printf("%d pointsInsideCircle from thread %d\n",pointsInCircleFromThread,threadNum);
    insideCircleCount += pointsInCircleFromThread;
    pthread_mutex_unlock(&mutex);


    return NULL;
}




int main(){
	//printf("hello");


	printf("Monte Carlo PI Estimation: \n\n");
	printf("Enter number of threads to use: ");
	int numOfThreads = 1;
	scanf("%d",&numOfThreads);

	if(numOfThreads <= 0){
		numOfThreads = 1;
	}

	//max rounds per thread is 4 * number of threads
	int maxRoundsPerThread = ((INT_MAX - 1)/(4*numOfThreads));

	printf("Enter number of rounds to perform per thread: (1-%d) ",maxRoundsPerThread);
	scanf("%d",&roundsPerThread);
	if(roundsPerThread <= 0){
		roundsPerThread = 1;
	}else if(roundsPerThread > maxRoundsPerThread){
		roundsPerThread = maxRoundsPerThread;
	}
	time_t startTime;
	time_t finishTime;
	time_t totalTime; 

	startTime = time(NULL); //generate current time

	//seed random function with current time

	srand(startTime);

	//alloc array of threads
	pthread_t *threads = malloc(numOfThreads * sizeof(pthread_t));

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    //create and run threads
    int i;
    for (i = 0; i < numOfThreads; i++) {
        pthread_create(&threads[i], &attr, MonteCarlo, (void *) NULL);
    }
    //wait for threads to finish
    for (i = 0; i < numOfThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    //delete threads and mutex lock
    pthread_mutex_destroy(&mutex);
    free(threads);


    double pi = ((double)(4*insideCircleCount))/(roundsPerThread*numOfThreads);

    //generate finish time
    finishTime = time(NULL);
    printf("%d threads with %d rounds per thread estimated PI to be: %f",numOfThreads,roundsPerThread,pi);

    totalTime = finishTime - startTime;
	printf("\nprogram finished in %ld seconds",totalTime);
	

	printf("\n");
	return 0;
}