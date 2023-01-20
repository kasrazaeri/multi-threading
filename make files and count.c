#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h> 



struct thread_data{
	char word[20];
    FILE *fp;
    long int offset; //the length of the part for each thread
    int start;		
    int counter;	 //the last output, number of word
};

//each thread run this function when created.
void *countFrequency(void* data){
	struct thread_data* td=data;
    char *buffer = malloc(td->offset);
    char c; 
   	int index = 0;
	bool flag = true;
	int n;
	n=100; /////////////////
	
	//the position of pointer,where to start the file  
    fseek(td->fp, td->start, SEEK_SET); 

	//read and store in the buffer
	fread(buffer, sizeof(char), td->offset, td->fp);
	int i;
	for(i = 0 ; i < (td->offset) ; i++)
	{	
   		c = *(buffer + i);		
   		if(c != NULL){
		    if(c == (td->word[index]) && flag == true){
		   	    index++;
		   	    if (index == strlen(td->word)){
		   		    td->counter++;
		   		    index = 0;
		   		}
		   	  continue;
		   	}
			
			if(c != (td->word)) 
			{ 
		   	    flag = true;
		   		index = 0;	
		    }
			
	    }
    }
    
    free(buffer);
    pthread_exit(NULL);
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



int main(int argc, char **argv){
    int id;
    long int blockSize;
    pthread_t *threads;
	char word[20] ;
	char *s;
	int j;
	int z;
	int i;
	int nthreads;
	char c;
	int m;
	m=20; //////////////////////number of files
	int n;
	n=100; /////////////////////////////length of text of file
	char file_list[m][30];
    FILE *fp[m];
    FILE *fp2[m];
	nthreads = 4 ; //you can change the number of threads
    struct thread_data data[nthreads];

	printf("Enter the word : ");
	scanf("%s",word);

clock_t begin = clock();


for (j=0;j<m;j++)
{

	sprintf(file_list[j] , "file%d.txt" , j);
	fp2[j] = fopen(file_list[j],"w");
		
	random_string(s, n);
    c = getc(fp2[j]);
    while (c==s[0])
    {
    	random_string(s,n);
	}
	///////////////////////////////////////////////////////////////////////////////
	
	fprintf(fp2[j] , "%s" , s);
	
    if (j==0)
    {
    	if (NULL != fp2[j]) 
		{
            fseek(fp2[j], 0, SEEK_END);
            int size = ftell(fp2[j]);


                if (0 == size) 
				{
                    fclose(fp2[j]);
                    fp2[j] =fopen("file0.txt","w");
                    random_string(s, n);
                    fprintf(fp2[j] , "%s" , s);

                }   
			    else 
				{
                    rewind(fp2[j]);
                }
        }    
    }
	///////////////////////////////////////////////////////////////

	fclose(fp2[j]);
}
for (z=0 ; z < m ; z++)
{
    fp[z]=fopen(file_list[z],"r") ; 
	

    threads = malloc(nthreads*sizeof(pthread_t)); //allocate memory to threads
		
    fseek(fp[z], 0, SEEK_END); // Moving pointer to end
    int len = ftell(fp[z]);    //position of pointer
			
    blockSize=(len+nthreads-1)/nthreads;

    for(id = 0; id < nthreads; id++){
		
        data[id].fp=fp[z];
        data[id].offset = blockSize;
        data[id].start = id*blockSize;
        data[id].counter = 0;

		// assign all the elements of one array to another one
        memcpy(data[id].word, word, strlen(word));
        data[id].word[strlen(word)] = NULL; //last element
    }
	
    for(id = 0; id < nthreads; id++)
        pthread_create(&threads[id], NULL, &countFrequency,&data[id]);
        
    for(id = 0; id < nthreads; id++) //main should wait for other threads
        pthread_join(threads[id],NULL);
        
    int counter = 0;
    for(id = 0 ; id < nthreads; id++){ //sum of all thread's results
    	counter = counter + data[id].counter;
    }
    printf("number of word in file %d is: ",z);
    printf("%d\n",counter); 

    fclose(fp[z]);
 
}
    clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("This process lasts %.3f miliseconds\n",time_spent*1000);

    return 0;  
}

