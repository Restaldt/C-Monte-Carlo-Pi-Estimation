#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>


//generates random doubles between max and min
double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main(){
	printf("Monte Carlo Pi Estimation: \n\n");
	//max rounds is INT_MAX / 4
	printf("Enter how many rounds of Monte Carlo you want to estimate pi with: (1-%d)",(INT_MAX-1)/4);
	int rounds = 0;
	scanf("%d",&rounds);


	int index;

	time_t startTime;
	time_t finishTime;
	time_t totalTime; 

	startTime = time(NULL); //generate current time

	//seed random function with current time

	srand(startTime);

	int insideCircleCount = 0;

	for(index = 0;index < rounds;index++){

		//generate random x,y coordinates 

		double x = randfrom(-1,1);
		double y = randfrom(-1,1);




		//if x^2 + y^2 < r^2 then the point falls within the circle

		if( (x*x) + (y*y) < 1){
			insideCircleCount++;
		}

		
	}
	finishTime = time(NULL);
	//printf("%d",insideCircleCount);


	double pi = (double)(4*insideCircleCount)/(rounds);
	printf("%d rounds of Monte Carlo estimated PI to be: %f",rounds,pi);
	totalTime = finishTime - startTime;
	printf("\nprogram finished in %ld seconds",totalTime);
	
	printf("\n");
	return 0;
}
 



