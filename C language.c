#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<stdbool.h>


int substring_count(char* string, char* substring) {
  int i, j, l1, l2;
  int count = 0;
  int found = 0;

  l1 = strlen(string);
  l2 = strlen(substring);

  for(i = 0; i < l1 - l2 + 1; i++) {
    found = 1;
    for(j = 0; j < l2; j++) {
      if(string[i+j] != substring[j]) {
        found = 0;
        break;
      }
    }

    if(found) {
      count++;
      i = i + l2 -1;
    }
  }

  return count;
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
int num;	
printf("m = please enter the number of files you want to create:\n");
scanf("%d", &num);
int length;
printf("n = enter the length of random alphabets in files:\n");
scanf("%d", &length);
int n;
int i;
i=0;
printf("tedade zir reshte hayi ke mikhahid baresi shavand ra vared konid:\n");
scanf("%d",&n);
char a[n][500];
int l_sub[n];
printf("zir reshte hayi ke mikhahid ra vared konid (ba Enter zir reshte baadi ra vared konid)\n");
for (i=0;i<n;i++)
{
	scanf("%s", &*a[i]);
	l_sub[i]=strlen(a[i]);
}

clock_t begin = clock();	/////////////////////////////////clock

char file_list[num][30];
FILE *fp[num];

for (i=0;i<num;i++)
{
	
	sprintf(file_list[i] , "file%d.txt" , i);
	fp[i] = fopen(file_list[i],"w");
	fclose(fp[i]);
}


FILE *fp2[num];
int counter;
int j;
counter=0; 
char s[length];
printf("please wait...\n"); 
char *data;      
char c;       
char temp[length+1];
int z;
char *buffer;
int count2;
count2=0;

for (j=0;j<num;j++)
{
	fp2[j] = fopen(file_list[j],"w");
		
	random_string(s, length);
    c = getc(fp2[j]);
    while (c==s[0])
    {
    	random_string(s,length);
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
                    random_string(s, length);
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
	fp2[j]= fopen(file_list[j],"r");

    for (i=0;i<n;i++)
    {
    	rewind(fp2[j]);
    	fread(temp , length, 1, fp2[j]);
    	temp[length] = 0; // terminate the string
        counter=counter+ substring_count(temp,a[i]);
        
	}
	
	fclose(fp2[j]);
	fp2[j] =fopen(file_list[j],"r");
	char c;
	char ch;
	c = getc(fp2[j]);
	
	////    
	////
	fclose(fp2[j]);
}



printf("it is done\n");
printf("tedade zir reshte ha dar file ha :%d\n",counter);
clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("This process lasts %.3f miliseconds\n",time_spent*1000);

return 1;
}
