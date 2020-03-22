#include <stdlib.h>
#include <stdio.h>
#include <string.h>



static int i;

void cpy(char *d, char *s, int n)
{
  while (n--!=0) *d++=*s++;
}

void foo(char *str, int s)
{
    char buffer[32];

    for(i = 0; i<sizeof(buffer); i++)
      buffer[i]=(char)255;
    
    /*
    printf("buffer AT %lx\n",(long)&buffer);
    for(i = 0; i<12; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);
    */

    cpy(buffer, str, s); /* buffer overflow here */
      
    /*
    printf("buffer after\n"); 
    for(i = 0; i<12; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);
    */
    
}

int main(int argc, char **argv)
{
    char str[400];
    FILE *badfile;
    int retval = 0;

    badfile = fopen("smasher", "r");
    int s = fread(str, sizeof(char), 400, badfile);
    foo(str,s);
    retval = 0;  // write a virus that changes the retval to 66
   
    return retval;
}

/* utils to inspect frame of foo */

   /* 
    for(int i = 0; i<sizeof(buffer); i++)
      buffer[i]=(char)255;
   */
   /* 
    printf("buffer AT %lx\n",(long)&buffer);
    for(int i = 0; i<8; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);
   */ 

    /*
    for(int i = 0; i<8; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);
    */
