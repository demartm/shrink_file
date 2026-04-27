#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
FILE *a, *b;

a = fopen("/home/root_user/shrink_file/test.txt","r");
b = fopen("/home/root_user/shrink_file/test2.txt","w+");

char *buff = (char*)calloc(1000,sizeof(char));

if(a){

  for(int i = 0; fread(buff,1,7,a) > 0; i += 7){

    unsigned char mask = 1;

    for(int j = 1; j < 7; j++ ){

      if(buff[0] & mask){

        buff[j] = buff[j] | 128;//10000000b
      }

      mask = mask << 1;
    }

    fwrite(&buff[1],1,6,b);

  }


}

return 0;
}
