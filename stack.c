#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Primeiro: gcc writer.c -o writer //ou entao com o writer0 sendo que a diferenca esta no writer0 ser o ficheiro inicial e o writer ser o ficheiro ja alterado pelo prof

//ter especial atencao ao nome do smasher ou smasherempty na main caso se use o writer.c ou o writer0.c

Segundo: ./writer   //ou entao ./writer0

Terceiro(para sempre que compilarmos o stack.c assim ja nao esta sempre a mudar o endereco do buffer e este fica constante): echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

Quarto: gcc -fno-stack-protector -D_FORTIFY_SOURCE=0 -W -no-pie stack.c -z execstack -o stack
Quinto: objdump -d stack
Sexto: ./stack
Setimo: echo $?

//O writer.c do prof esta feito para o mac e consegue alteraro valor para 66 mas como eu estou a usar ubuntu ao testar conseguimos na mesma alterar o valor de retval mas para 139 em vez dos 66. Falta ver melhor a fundo e modificar bem o writer0.c para modificar o retval para 66
*/

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
