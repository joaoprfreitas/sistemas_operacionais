#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE_VECTOR 100
int sum;  /* this data is not shared by the process(s) */

void delay(int seconds) {	
	int start = clock();
	// wait n seconds
    while (((clock()-start)/CLOCKS_PER_SEC)<seconds);         
}

void runner(int param) {
	int i, upper = param;
	sum = 0;
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	delay(10);
    printf("sum = %d\n",sum);
}

int vectorA[SIZE_VECTOR];
int vectorB[SIZE_VECTOR];
int vectorC[SIZE_VECTOR];

int main() {
    for (int i = 0; i < SIZE_VECTOR; i++) {
        vectorA[i] = i;
        vectorB[i] = SIZE_VECTOR - i;	
        printf("vectorA[i] = %d vectorB[i] = %d \n", vectorA[i], vectorB[i]);
    }

    for (int i = 0; i < 5; i++) { // loop will run n times (n=5)
        if (fork() == 0) {
            printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
            for (int i = 0; i < SIZE_VECTOR; i++) {
	            vectorC[i] = vectorA[i] + vectorB[i];
	            printf("vectorC[i] = %d\n", vectorC[i]);	 	
	        }
            return 0;
        }
    }

    for (int i = 0; i < 5; i++)
        wait(NULL);
      
    return 0;
}