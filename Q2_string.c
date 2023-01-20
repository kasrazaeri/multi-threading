#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include<stdbool.h>
#include<semaphore.h>



#define NTHREADS10
#define LINE 1000

FILE *fp;
pthread_mutex_t writer_lock = PTHREAD_MUTEX_INITIALIZER;
FILE *fp2;
int m;
m=2 ;          /////////// enter the number of files you want to create
int n;
n=20000 ;        /////////// enter the number of alphabets you want to write in files
int p;
int NTHREADS ;
NTHREADS = 4 ;           //////////////////////Nthread
int co;
co=0;

void* reader(void* args)
{

int id = *((int*)args);
char output[LINE];	

printf("Thread %d is reading now\n",id);

// Critical section for the readers - first reading thread locks so writers cannot write to file and last reading thread unlocks allowing writer to write
pthread_mutex_lock(&writer_lock);	
fgets(output,LINE,fp2);
pthread_mutex_unlock(&writer_lock);

return NULL;
}


void* writer(void* args)
{
char input[1000][1000];
random_string(input,n);
int id = *((int*)args);
printf("Thread %d is making and writing file now\n",id);

pthread_mutex_trylock(&writer_lock);
fwrite(input,1,strlen(input),fp);
pthread_mutex_unlock(&writer_lock);
input==0;
sleep(25);
return NULL;

}


void random_string(char  *string, int length)
{
    char pool[] = "abcdefghijklmnopqrstuvwxyz";
    int poolsize = strlen(pool) ;
    int index;
    int i;


    for(i = 0; i < length > 0; i++)
    {
        index = rand() % poolsize;       // a random index into the pool
        string[i] = pool[index];         // take that character
    }

    string[i]= '\0';
}



int main()
{
clock_t begin = clock();
char file_list[m][1000];
int p;
int n;
n=20000;/////////////////////////
char *string;



for (p=0;p<m;p++)
{



pthread_t thread_ids[NTHREADS];

// Create threads
int i;

for( i = 0; i < NTHREADS ; i++)
{
	if(pthread_create( &thread_ids[i], NULL, writer, (void *)&thread_ids[i]) != 0)
	{
		puts("Unable to create threads. Exiting now...");
		return 1;
	}
}
	
fclose(fp);



fp2 = fopen(file_list[p],"r");

for(i = 0; i < NTHREADS ; i++)
{
	if(pthread_create( &thread_ids[i], NULL, reader, (void *)&thread_ids[i]) != 0)
	{
		puts("Unable to create threads. Exiting now...");
		return 1;
	}
}

// Join the threads

for(i = 0; i < NTHREADS ; i++)
{
	if(pthread_join(thread_ids[i],NULL) != 0)
	{
		puts("Unable to join threads. Cleaning up and exiting now...");
		return 1;
	}
}

// Clean up
pthread_mutex_destroy(&writer_lock);


}
clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("This process lasts %.3f miliseconds\n",time_spent*1000);
return 0;
}


