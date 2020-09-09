/* Program: Speedup calculation of matrix multiplication with
 *          multi-processing and multi-threading.
 * Author:  Sai Balaram Korrapati
 * Roll# :  ES18BTECH11011
 */
#include <stdlib.h> /* for exit, atoi */
#include <stdio.h>  /* for fprintf */
#include <errno.h>  /* for error code eg. E2BIG */
#include <getopt.h> /* for getopt */
#include <assert.h> /* for assert */ //
#include<time.h>	/* for time */
#include<unistd.h>
#include<malloc.h>	/* for allocating memory */
#include<semaphore.h> 
#include<pthread.h>	
#include <sys/shm.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include<sys/time.h>
 
double t_sing,t_multi_thread,t_multi_process;
sem_t mutex;   	//semaphore variable
int num1=0;
int num2=0;
int nof_threads=0;
int nof_process=0;	//initialising variables

void usage(int argc, char *argv[]);
void input_matrix(int *mat, int nrows, int ncols);
void output_matrix(int *mat, int nrows, int ncols);

void init_matrix(int *mat,int rows,int cols);
unsigned long long  single_thread_mm();
unsigned long long  multi_thread_mm();
unsigned long long  multi_process_mm();
void mul();// initialsing functions

int *A, *B, *C;
int crows, ccols;
int arows, acols, brows, bcols;
char interactive = 0;

int main(int argc, char *argv[])
{
	int c;
	/* Loop through each option (and its's arguments) and populate variables */
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"help",	no_argument,		0, 'h'},
			{"ar",		required_argument,	0, '1'},
			{"ac",		required_argument,	0, '2'},
			{"br",		required_argument,	0, '3'},
			{"bc",		required_argument,	0, '4'},
			{"interactive",	no_argument, 		0, '5'},
			{0,		0,			0,  0 }
		};

		c = getopt_long(argc, argv, "h1:2:3:4:5", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			fprintf(stdout, "option %s", long_options[option_index].name);
			if (optarg)
				fprintf(stdout, " with arg %s", optarg);
				fprintf(stdout, "\n");
			break;

		case '1':
			arows = atoi(optarg);
			break;

		case '2':
			acols = atoi(optarg);
			break;

		case '3':
			brows = atoi(optarg);
			break;

		case '4':
			bcols = atoi(optarg);
			break;

		case '5':
			interactive = 1;
			break;

		case 'h':
		case '?':
			usage(argc, argv);

		default:
			fprintf(stdout, "?? getopt returned character code 0%o ??\n", c);
			usage(argc, argv);
		}
	}

	if (optind != argc) {
		fprintf(stderr, "Unexpected arguments\n");
		usage(argc, argv);
	}

	unsigned long long time_single, time_multi_process, time_multi_thread; 
	sem_init(&mutex, 0, 1);		//initialsing semaphore variable mutex to 1
	if(acols != brows)			// if acols not equal to brows then we exit failure to the shell
	{
		exit(EXIT_FAILURE);
	}	
	time_single = 	single_thread_mm();		//calling the function for single thread and assigning the time to time_single variable
	time_multi_thread =	multi_thread_mm();	//calling the function for multi thread and assigning the time to time_multi_thread variable	
	time_multi_process= multi_process_mm(); //calling the function for multi process and assigning the time to time_multi_process variable	

	fprintf(stdout, "Time taken for single threaded: %llu us\n",
			time_single);
	fprintf(stdout, "Time taken for multi process: %llu us\n",
			time_multi_process);
	fprintf(stdout, "Time taken for multi threaded: %llu us\n",
			time_multi_thread);
	fprintf(stdout, "Speedup for multi process : %4.2f x\n",
			(double)time_single/time_multi_process);
	fprintf(stdout, "Speedup for multi threaded : %4.2f x\n",
			(double)time_single/time_multi_thread);					//printing the times taken for each process and 

	exit(EXIT_SUCCESS);
}
/* 
 Show usage of the program
*/
void usage(int argc, char *argv[])
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s --ar <rows_in_A>  --ac <cols_in_A>"
			" --br <rows_in_B>  --bc <cols_in_B>"
			" [--interactive]",
			argv[0]);
	exit(EXIT_FAILURE);
}

void init_matrix(int *mat,int rows,int cols)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			*(mat+(i*cols+j)) = rand(); 		//noninteractive mode assigning random into the matrix 
		}
	}
}
/* 
 Input a given 2D matrix
*/
void input_matrix(int *mat, int rows, int cols)
{
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			fscanf(stdin, "%d", mat+(i*cols+j));
		}
	}
}
/* 
  Output a given 2D matrix
*/
void output_matrix(int *mat, int rows, int cols)
{
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			fprintf(stdout, "%d ", *(mat+(i*cols+j)));
		}
		fprintf(stdout, "\n");
	}
}

unsigned long long single_thread_mm()
{
	A = (int *)malloc(arows*acols*sizeof(int));
	B = (int *)malloc(brows*bcols*sizeof(int));
	C = (int *)malloc(arows*bcols*sizeof(int));		//allocating space to the matrices
	if(interactive == 1)
	{
		fprintf(stdout, "Enter A:\n");
		input_matrix(A,arows,acols);
		fprintf(stdout, "Enter B:\n");	//if interactive taking input from the user
		input_matrix(B,brows,bcols);		
	}
	else
	{
		init_matrix(A,arows,acols);	//generate random into the matrix
		init_matrix(B,brows,bcols);
	}
	int i=0,j=0,k=0;
	struct timeval start, end;
	gettimeofday(&start, NULL);//measuring time start
	for(i=0;i<arows;i++)								//start clock
	{
		for(j=0;j<bcols;j++)
		{
			*(C+(i*bcols+j)) = 0;
			for(k=0;k<brows;k++)
			{
				*(C+(i*bcols+j)) = (*(C+(i*bcols+j))) +  (*(A+(i*brows+k)))*(*(B+(k*bcols+j)));			//computing multiplication
			}
		}
	}
	gettimeofday(&end, NULL);							//end clock
	t_sing = (end.tv_sec - start.tv_sec)*1000000;		//calculating the time for the multiplication to be performed	
	t_sing = (t_sing + (end.tv_usec - start.tv_usec));
	if(interactive==1)
	{
		fprintf(stdout, "Result:\n");
		output_matrix(C,arows,bcols);//printing the matrix if it is interactive
	}
	free(A);
	free(B);
	free(C);//freeing the allocated memory
	return t_sing;//returning the time
}

void mul()
{
	sem_wait(&mutex);
	int count = num1++;//locking the thread so that context switch does not hapen and incrementing the count and assigning the corresponding thread a certain amount of rows of multiplication to perform
	sem_post(&mutex);
	for(int i=count*arows/nof_threads;i<(count + 1)*arows/nof_threads;i++)				//allocating certain number of rows and columns to the thread to perform multiplication 
	{
		for(int j=0;j<bcols;j++)
		{
			*(C+(i*bcols+j)) = 0;
			for(int k=0;k<brows;k++)
			{
				*(C+(i*bcols+j)) = *(C+(i*bcols+j)) +  (*(A+(i*brows+k)))*(*(B+(k*bcols+j)));		//computing multiplication
			}
		}
	}
	
}

unsigned long long  multi_thread_mm()
{
	A = (int *)malloc(arows*acols*sizeof(int));
	B = (int *)malloc(brows*bcols*sizeof(int));
	C = (int *)malloc(arows*bcols*sizeof(int));		//allocating space to the matrices
	if(interactive == 1)
	{
		fprintf(stdout, "Enter A:\n");
		input_matrix(A,arows,acols);
		fprintf(stdout, "Enter B:\n");		//if interactive taking input from the user
		input_matrix(B,brows,bcols);		
	}
	else
	{
		init_matrix(A,arows,acols);//generate random into the matrix
		init_matrix(B,brows,bcols);
	}
	nof_threads = 11;

	pthread_t pid[nof_threads];
	int i=0;
	//int stat;
	struct timeval start, end;
	gettimeofday(&start, NULL);

	for(i=0;i<nof_threads;i++)
	{
		pthread_create(&pid[i],NULL,(void *)mul,NULL);			//creating threads and erforming multiplication
	}
	for(i=0;i<nof_threads;i++)
	{
		pthread_join (pid[i], NULL);					//the parent process waiting for the child process
	}
	gettimeofday(&end, NULL);
	t_multi_thread = (end.tv_sec - start.tv_sec)*1000000;		//calculating the time for the multiplication to be performed	
	t_multi_thread = (t_multi_thread + (end.tv_usec - start.tv_usec));
	if(interactive == 1)
	{
		fprintf(stdout, "Result:\n");
		output_matrix(C,arows,bcols);	//if interactive printing
	}
	free(A);
	free(B);
	free(C);//deallocating the memory allocated
	return t_multi_thread;//returning the time 
}


//multi process
unsigned long long  multi_process_mm()
{
	int shm_id1 = shmget(IPC_PRIVATE, arows*acols*(sizeof(int)), IPC_CREAT | 0666);
	int shm_id2 = shmget(IPC_PRIVATE, brows*bcols*(sizeof(int)), IPC_CREAT | 0666);
	int shm_id3 = shmget(IPC_PRIVATE, arows*bcols*(sizeof(int)), IPC_CREAT | 0666);		//creating shared memory with read,write to shared memoey
	A = (int *)shmat(shm_id1,NULL,0);
	B = (int *)shmat(shm_id2,NULL,0);		//allocating the created shared memory to the matrices so that they can be modified also by the child process
	C = (int *)shmat(shm_id3,NULL,0);
	if(interactive == 1)
	{
		fprintf(stdout,"Enter A:\n");
		input_matrix(A,arows,acols);
		fprintf(stdout,"Enter B:\n");		//if interactive taking the input
		input_matrix(B,brows,bcols);
	}
	else
	{
		init_matrix(A,arows,acols);
		init_matrix(B,brows,bcols);
	}
	nof_process = 5;
//	multi_process_start = clock();
	struct timeval start, end;
	gettimeofday(&start, NULL);
	for(int p=0;p<nof_process;p++)
	{
		fflush(stdout);						//flushing the output in cache memory from the parent so that it does not get copied to the child
		
		pid_t id = fork();
		if(id == 0)
		{
			for(int i=p*arows/nof_process;i<(p+1)*arows/nof_process;i++)				//allocating a child process certain amount of work to be done
			{
				for(int j=0;j<bcols;j++)
				{
					*(C+(i*bcols+j)) = 0;
					for(int k=0;k<brows;k++)
					{
						*(C+(i*bcols+j)) = *(C+(i*bcols+j)) +  (*(A+(i*brows+k)))*(*(B+(k*bcols+j)));			//computing the matrix
					}
				}
			}
			exit(0);						//process will exit when it's work is done
		}
	}
	for(int i=0;i<nof_process;i++)
	{
		wait(NULL);						//parent waiting for the child process
	}
	gettimeofday(&end, NULL);						//end the clock 
	t_multi_process = (end.tv_sec - start.tv_sec)*1000000;			//calculating the time taken for matrix multiplication
	t_multi_process = (t_multi_process + (end.tv_usec - start.tv_usec));

	if(interactive == 1)
	{
		fprintf(stdout,"Result:\n");
		output_matrix(C,arows,bcols);			//if interactive printing the memory
	}
	shmdt(A);
	shmdt(B);
	shmdt(C);								//detach the memory allocated to it
	shmctl(shm_id1, IPC_RMID, NULL);
	shmctl(shm_id2, IPC_RMID, NULL);
	shmctl(shm_id3, IPC_RMID, NULL);		//deleting the shared memory created 
	return t_multi_process;					//returning the time
}