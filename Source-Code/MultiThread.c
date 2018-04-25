#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define NOOFTHREADS 2
#define MAX_SIZE 1024  
int array[MAX_SIZE];

typedef struct node {
    int i;
    int j;
} NODE;

void merge(int i, int j)
{
        int mid = (i+j)/2;
        int k = i;
        int l = mid+1;

        int newArray[j-i+1], newK = 0;

        while(k <= mid && l <= j) {
                if (array[k] > array[l])
                        newArray[newK++] = array[l++];
                else                    
                        newArray[newK++] = array[k++];
        }

        while(k <= mid) {
                newArray[newK++] = array[k++];
        }

        while(l <= j) {
                newArray[newK++] = array[l++];
        }

        for (k = 0; k < (j-i+1) ; k++)
                array[i+k] = newArray[k];

}

void * mergesort(void *a)
{
        NODE *p = (NODE *)a;
        NODE n1, n2;
        int mid = (p->i+p->j)/2;
        pthread_t tid1, tid2;
        int ret;

        n1.i = p->i;
        n1.j = mid;

        n2.i = mid+1;
        n2.j = p->j;

        if (p->i >= p->j)
	 return 0;

	
        ret = pthread_create(&tid1, NULL, mergesort, &n1);
        if (ret) {
                
	printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);    
                exit(1);
        }


        ret = pthread_create(&tid2, NULL, mergesort, &n2);
        if (ret) {
                printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);    
                exit(1);
        }

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(p->i, p->j);
        pthread_exit(NULL);
}


int main()
{
        int i;
        NODE n;
	// generating random numbers in array
	srand(time(NULL));
  	printf("Unsorted Array:\n");
  	for (i=0;i<MAX_SIZE;i++){
        	array[i]=rand()%100;
 		printf("%d ",array[i]);
	}
	printf("\n");

        n.i = 0;
        n.j = MAX_SIZE-1;
        pthread_t tid;


	
        int ret; 
	// startingTime and endingTime for calculating time for merge sort
    	clock_t startingTime, endingTime;
 	startingTime=clock();
        ret=pthread_create(&tid, NULL, mergesort, &n);
        if (ret) 
	{
                printf("%d %s - unable to create thread - ret - %d\n", __LINE__,__FUNCTION__, ret);    
                exit(1);
        }

        pthread_join(tid, NULL);
	endingTime = clock();
	printf("Sorted Array:\n");

        for (i = 0; i < MAX_SIZE; i++)
               printf ("%d ", array[i]);

        printf ("\n");

    // calculating time taken in applying merge sort
    printf("Time taken: %f\n",(endingTime - startingTime)/(double)CLOCKS_PER_SEC);
        // pthread_exit(NULL);
        return 0;
}
