// C program to implement concurrent merge sort using multiprocess of 2 Process 
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
 
void insertionSort(int arr[], int n);
void merge(int arr[], int low1, int high1, int high2);
 
void mergeSort(int arr[], int low, int high)
{
    int i, len=(high-low+1);
 
    // Using insertion sort for small sized array
    if (len<=5)
    {
        insertionSort(arr+low, len);
        return;
    }
 
    pid_t lpid,rpid;
    lpid = fork();
    if (lpid<0)
    {
        // Lchild proc not created
        perror("Left Child Proc. not created\n");
        _exit(-1);
    }
    else if (lpid==0)
    {
	printf ("Left Process Running \n ");
        mergeSort(arr,low,low+len/2-1);
        _exit(0);
    }
    else
    {
        rpid = fork();
        if (rpid<0)
        {
            // Rchild proc not created
            perror("Right Child Proc. not created\n");
            _exit(-1);
        }
        else if(rpid==0)
        {
	    printf ("Right Process Running \n ");
            mergeSort(arr,low+len/2,high);
            _exit(0);
        }
    }
 
    int status;
 
    // Wait for child processes to finish
    waitpid(lpid, &status, 0);
    waitpid(rpid, &status, 0);
 
    // Merge the sorted subarrays
    merge(arr, low, low+len/2-1, high);
}
 
/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
       /* Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}
 
// Method to merge sorted subarrays
void merge(int arr[], int low1, int high1, int high2)
{
    // We can directly copy  the sorted elements in the final array, no need for a temporary sorted array.
    int count=high2-low1+1;
    int sortedArray[count];
    int i=low1, k=high1+1, m=0;
    while (i<=high1 && k<=high2)
    {
        if (arr[i]<arr[k])
            sortedArray[m++]=arr[i++];
        else if (arr[k]<arr[i])
            sortedArray[m++]=arr[k++];
        else if (arr[i]==arr[k])
        {
            sortedArray[m++]=arr[i++];
            sortedArray[m++]=arr[k++];
        }
    }
 
    while (i<=high1)
        sortedArray[m++]=arr[i++];
 
    while (k<=high2)
        sortedArray[m++]=arr[k++];
 
    int arr_count = low1;
    for (i=0; i<count; i++,low1++)
        arr[low1] = sortedArray[i];
}
 
// To check if array is actually sorted or not
void isSorted(int arr[], int len)
{
    if (len==1)
    {
        printf("Sorting Done Successfully\n");
        return;
    }
 
    int i;
    for (i=1; i<len; i++)
    {
        if (arr[i]<arr[i-1])
        {
            printf("Sorting Not Done\n");
            return;
        }
    }
    printf("Sorting Done Successfully\n");
    return;
}
 
// To fill randome values in array for testing
// purpise
void TakingInput(int arr[], int len)
{
    // Create random arrays
    int i;
    for (i=0; i<len; i++)
	{
	arr[i] = rand()%100;
	printf ("%d ",arr[i]);
	}	
    return;
}

 
// Driver code
int main()
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;
 
 
    // Using fixed size array.  We can uncomment
    // below lines to take size from user
    int length;
 
    printf("Enter No of elements of Array:");
    scanf("%d",&length); 
 
    // Calculate segment length
    size_t SHM_SIZE = sizeof(int)*length;
 
    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }
 
    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *) -1)
    {
        perror("shmat");
        _exit(1);
    }
 
    // Create a random array of given length
    srand(time(NULL));
    TakingInput(shm_array, length);
	printf ("\n");
   // startingTime and endingTime for calculating time for merge sort
    	clock_t startingTime, endingTime;
 	startingTime=clock();
        
    // Sort the created array
    mergeSort(shm_array, 0, length-1);
    endingTime = clock();
    // Check if array is sorted or not
    isSorted(shm_array, length);
	for (int i=0;i<length;i++)
	{
		printf ("%d ",shm_array[i]);
	}
	printf ("\n");
 
    /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }
 
    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
 // calculating time taken in applying merge sort
    printf("Time taken: %f\n",(endingTime - startingTime)/(double)CLOCKS_PER_SEC);
    
    return 0;
}
