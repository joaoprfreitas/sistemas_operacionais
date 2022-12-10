#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

int sum;  /* this data is not shared by the process(s) */

void delay(int seconds){	
	int start = clock();
	// wait n seconds
    while (((clock() - start) / CLOCKS_PER_SEC) < seconds);         
}

void runner(int param){
	int i, upper = param;
	sum = 0;
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	delay(10);
    printf("sum = %d\n",sum);
}

int main() {
    pid_t pid;

	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		return EXIT_FAILURE;
	}
	else if (pid == 0) { /* child process */
		printf("I am the child %d\n",pid);
        while(1) {
            
        }
		runner(3);		
		execlp("/bin/ls","ls",NULL);
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		printf("I am the parent %d\n",pid);
		runner(4);		
		// wait(NULL);
		
		printf("Child Complete\n");
	}
    
    return EXIT_SUCCESS;
}
