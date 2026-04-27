#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void pack_file(FILE *a,FILE *b){

if(a && b){

  unsigned char *buff = (unsigned char*)calloc(7,sizeof(unsigned char));

    if(buff){
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

}

void unpack_file(FILE *a, FILE *b){

if(a && b){

  unsigned char *buff = (unsigned char*)calloc(7,sizeof(unsigned char));

  if(buff){

    size_t read = 0;

    while((read = fread(&buff[1],1,6,a)) == 6){
      buff[0] = 0;
      unsigned char mask = 128;

      for(int i = 1; i < 7; i++){

        buff[0] = buff[0] | (buff[i] & mask);
        buff[0] = buff[0] >> 1;

        buff[i] = buff[i] & (~mask);

      }

      buff[0] = buff[0] >> 1;

      fwrite(buff,1,7,b);

    }

    if(read > 0){
      fwrite(buff,1,read,b);
    }


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

pack_file(a,b);

fclose(a);
fclose(b);

FILE *c = fopen("/home/root_user/shrink_file/test2.txt","rb");
FILE *d = fopen("/home/root_user/shrink_file/test3.txt","wb+");

if(c && d){
unpack_file(c,d);

}
fclose(a);
fclose(b);

}

}


return 0;
}
