#include <stdio.h>
#include <stdbool.h>
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


bool compare(FILE *a, FILE *b){

if(a && b){
  unsigned char buf_a = 0;
  unsigned char buf_b = 0;

  bool is_end =false;

  while(fread(&buf_a,1,1,a) && fread(&buf_b,1,1,b)){

    if(buf_a != buf_b){

      return false;
    }

  }
  return true;
}
return false;

}

int main()
{

FILE *a = NULL;
FILE *b = NULL;

a = fopen("test.txt","rb");
if(!a){
  printf("unable to open file");

  return 0;
}

b = fopen("test2.txt","wb");
if(!b){
  printf("unable to open file");

  fclose(a);

  return 0;
}

if(!pack_file(a,b)){
  printf("error packing file");

  fclose(a);
  fclose(b);

  return 0;
}
fclose(a);
fclose(b);


FILE *c = NULL;
FILE *d = NULL;

c = fopen("test2.txt","rb");

if(!c){
  printf("unable to open file");

  return 0;
}

d = fopen("test3.txt","wb+");

if(!d){
  printf("unable to open file");

  fclose(c);

  return 0;
}


if(!unpack_file(c,d)){
  printf("error unpacking file");

  fclose(c);
  fclose(d);

  return 0;
}

  fclose(c);
  fclose(d);

FILE *e = NULL;
FILE *f = NULL;

e = fopen("test2.txt","rb");

if(!e){
  printf("unable to open file");

  return 0;
}

f = fopen("test3.txt","rb");

if(!f){
  printf("unable to open file");

  fclose(e);

  return 0;
}

if(!compare(e,f)){
printf("incorrect unpacking");
  fclose(e);
  fclose(f);
return 0;
}


// FILE *a, *b;

// a = fopen("test.txt","r");

// if(a){

// b = fopen("test2.txt","wb+");

// if(b){

// if(!pack_file(a,b)){
// printf("error1");
// }

// fclose(a);
// fclose(b);

// FILE *c = fopen("test2.txt","rb");
// FILE *d = fopen("test3.txt","wb+");

// if(c && d){
// if(!unpack_file(c,d)){

// printf("error2");
// }

// }
// fclose(c);
// fclose(d);

// }

// }

  fclose(e);
  fclose(f);

return 0;
}
