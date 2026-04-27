#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool pack_file(FILE *a,FILE *b){

if(a && b){

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

    if(buff){
      size_t read = 0;

      while((read = fread(buff,1,8,a)) == 8){

          unsigned char mask = 1;

          for(int j = 1; j < 8; j++){

            if(buff[0] & mask){

              if(buff[j] & 128){

                return false;
              }

              buff[j] = buff[j] | 128;//10000000b
            }

            mask = mask << 1;
          }

          if(!fwrite(&buff[1],1,7,b)){

            return false;
            }

        }

      if(read > 0){

        if(!fwrite(buff,1,read,b)){

          return false;
        }
      }

    return true;
    }
}
return false;
}

bool unpack_file(FILE *a, FILE *b){

if(a && b){

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

  if(buff){

    size_t read = 0;

    while((read = fread(&buff[1],1,7,a)) == 7){
      buff[0] = 0;
      unsigned char mask = 128;

      for(int i = 1; i < 8; i++){

        buff[0] = buff[0] | (buff[i] & mask);
        buff[0] = buff[0] >> 1;

        buff[i] = buff[i] & (~mask);

      }

      //buff[0] = buff[0] >> 1;

      if(!fwrite(buff,1,8,b)){
        return false;
      }

    }

    if(read > 0){

      if(!fwrite(&buff[1],1,read,b)){

        return false;
      }
    }

  return true;
  }


}

return false;
}


int main()
{
FILE *a, *b;

a = fopen("test.txt","r");

if(a){

b = fopen("test2.txt","wb+");

if(b){

if(!pack_file(a,b)){
printf("error1");
}

fclose(a);
fclose(b);

FILE *c = fopen("test2.txt","rb");
FILE *d = fopen("test3.txt","wb+");

if(c && d){
if(!unpack_file(c,d)){

printf("error2");
}

}
fclose(c);
fclose(d);

}

}


return 0;
}
