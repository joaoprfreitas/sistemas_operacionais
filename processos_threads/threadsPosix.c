#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */

void delay(int seconds){	
	int start = clock();
	// wait n seconds
    	while (((clock()-start)/CLOCKS_PER_SEC)<seconds);         
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) {
    int i, upper = atoi(param);
	sum = 0;
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	delay(10);

	pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t tid; /* the thread identifier */
    printf("tid = %lu\n",tid);

    pthread_attr_t attr; /* set of attributes for the thread */

    delay(1);

    if (argc != 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        /*exit(1);*/
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        /*exit(1);*/
        return -1;
    }

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);

    /* now wait for the thread to exit */
    pthread_join(tid, NULL);

    printf("sum = %d\n",sum);
}

