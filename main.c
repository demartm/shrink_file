#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void shrink_file(FILE *a,FILE *b){

char *buff = (char*)calloc(1000,sizeof(char));

if(a){

  size_t read = 0;

  while((read = fread(buff,1,7,a)) == 7){

      unsigned char mask = 1;

      for(int j = 1; j < 7; j++ ){

        if(buff[0] & mask){

          buff[j] = buff[j] | 128;//10000000b
        }

        mask = mask << 1;
      }

      fwrite(&buff[1],1,6,b);

    }

  if(read > 0){

    fwrite(buff,1,read,b);
  }


}
}

int main()
{
FILE *a, *b;

a = fopen("/home/root_user/shrink_file/test.txt","r");

if(a){

b = fopen("/home/root_user/shrink_file/test2.txt","wb+");

if(b){

shrink_file(a,b);

}

}

fclose(a);
fclose(b);
return 0;
}
