## WELCOME TO OS-PROJECT 2018
## PROJECT DETAILS:

### Operating System Spring 2018 Project FAST-NU Karachi, Pakistan

#Team Members: 
- **[Huzaifah Punjani 16K-3924](https://github.com/huzaifahpunjani)
- [Taban Shaukat 16K-3937](https://github.com/tabanshaukat)
- [Fareeha Sattar Shaikh 16K-3934](https://github.com/Fareeha-Sattar)

Submitted to: [Miss Sumaiyah Zahid](https://github.com/sumaiyah-zahid)

### OBJECTIVE:
Our project will mainly focus on the differences between multithreading and multiprocessing. The performance comparison will be observed by the implementation of merge sort. check out our [CODES Here](https://github.com/huzaifahpunjani/Project-OS/tree/master/Source-Code) and project [report here](https://github.com/huzaifahpunjani/Project-OS/blob/master/OS_PROJECT_REPORT_16K3924_16K3934_16K3937.docx).

### INTRODUCTION:
We will show the comparison by implementing sorting algorithm i.e. **Merge Sort** in different ways: using multithreading and multiprocessing. We will compare the performance of this sorting algorithm with respect to time, number of inputs and speed in relation with multiple threads and multiple processes.

### PROGRAMMING PLATFORM USED:
- The programming platform used is **C Language**.
- The operating system that we worked on is **Ubuntu**.
- **Git** and **github**.

### METHODOLOGY:
For a single thread and a single process, we implemented a single of merge sort.
For multithreading, we have used the library of pthread to create multiple threads and have joined the threads after merging of split parts while applying merge sort, whereas, for process, we have used the ipc and shm library with fork function to create 2 child processes then we called merge sort for both the processes on equal halves of number of elements attaching shared memory so that both processes concurrently work on the same memory space. Their sorted results were then merged and the shared memory was detached.
to split the number of elements in equal halves to make them sorted through merge sort technique with shared memory implemented through ipc and shm library functions. We can see that when number of threads and process were one no difference was there. But, when number of process and threads were increased to two, number of threads worked more slowly as compare to two processes for the same number of elements. The speed is achieved by dividing the execution time of the sequential version over the execution

### INSTALLATION & CODE PROCESS:

- Open up Terminal By pressing Ctrl + Alt + T
- Type sudo apt-get install git to install git on your Linux machine.
- After the installation is complete, type git clone https://github.com/huzaifahpunjani/Project-OS.git
- Navigate to the target directory through terminal by cd Project-OS/CODES/
- Compile the codes by typing gcc -o ObjectFileName (ProgramName.c)* (-lpthread)***
- Execute the compiled program by typing ./ObjectFileName

*It contains three Source codes named mergesort, MultiProcesses, & MultiThread***

### APPLICATION:
Multithreading and Multi Processing are two ways. Both have their respective usage, but nowadays multithreading is more widely used rather than multiprocessing. Because multiprocessing creates a overhead of PCBs in huge computations. 
Web servers, games like Angry birds, text editors to check errors and web browsers to create multiple tabs uses Multithreading.
Multiprocessing were used before the threads. It is not widely used nowadays. 

### CONCLUSION:
The conclusion which can be drawn from the graphs is that Merge sort is working faster in Multiprocessing as compared to multithreading. The reason is that, multithreading is creating an overhead of synchronization of the threads, secondly as merge sort works on divide and conquer rule so we have to merge all the parts at the end which is time consuming and there are architecture limitations too. Secondly, multithreading works faster on heavy computations. 

If you like our work, Do star it.
Share,
Team FTH
