#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>

bool pack_file(FILE *a,FILE *b, size_t *len){

if(a && b){

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

    if(buff){
      size_t read = 0;

      while ((read = fscanf(a,"%c",buff)) == 1){
      for(int i = 1; i < 8 && fscanf(a,"%c",&buff[i]) == 1;i++){
              if(buff[i] & 128){

                return false;
              }
        read++;
      }

      if(read == 8){//printf("%s",buff);
          unsigned char mask = 1;

          for(int j = 1; j < 8; j++){

            if(buff[0] & mask){



              buff[j] = buff[j] | 128;//10000000b
            }

            mask = mask << 1;
          }


        for(int i = 1;i < 8;i++){

          if(fprintf(b,"%c",buff[i]) != 1) {
            return false;
          }else{
            (*len)++;
          }
        }

        }else{
      if(read > 0){

        for(int i = 0; i < read; i++){

          if(fprintf(b,"%c",buff[i]) != 1){

            return false;
           }// else {

          //   //(*len)++;
          // }

}
        // if(!fwrite(buff,1,read,b)){

        //   return false;
        // }else{
        //   (*len)++;
        // }
      }
}
}
  free(buff);
  return true;

}
}
return false;
}

bool unpack_file(FILE *a, FILE *b, size_t len){

if(a && b){

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

  if(buff){

    size_t ix = 0;
  unsigned char mask = 128;//10000000b

  while(ix < len){

  buff[0] = 0;

  for(int i = 1; i < 8; i++){
    if(fscanf(a,"%c",&buff[i]) == 1){

      buff[0] = buff[0] | (buff[i] & mask);
      buff[0] = buff[0] >> 1;
      //printf(" %d",buff[0]);
      buff[i] = buff[i] & (~mask);
      ix++;
    } else {

      return false;
    }
  }

  for(int i = 0; i < 8; i++){

    if(fprintf(b,"%c",buff[i]) != 1){

      return 0;
    }
  }
}
  while(fscanf(a,"%c",buff) == 1){

      if(!fprintf(b,"%c",buff[0])){

        return 0;
      }
  }

  free(buff);
  return true;
}

}
return false;
}


bool compare(FILE *a, FILE *b){

if(a && b){
  unsigned char buf_a = 0;
  unsigned char buf_b = 0;
  int n1 = 0;
  int n2 = 0;
  bool is_end = false;
  while(!is_end){

  n1 = fscanf(a,"%c",&buf_a);
  n2 = fscanf(b,"%c",&buf_b);

  if((n1 == 1) || (n2 == 1)){

    if((n1 == 1) && (n2 == 1)){

      if(buf_a != buf_b){
        return false;
      }
    } else {
      return false;
    }
  } else{
    is_end = true;
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
size_t len = 0;

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

if(!pack_file(a,b,&len)){
  printf("error packing file");

  fclose(a);
  fclose(b);

  return 0;
} else{

printf("%d",len);
  printf("\nfile packed successfully");
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


if(!unpack_file(c,d,len)){
  printf("\nerror unpacking file");

  fclose(c);
  fclose(d);

  return 0;
}

  fclose(c);
  fclose(d);

FILE *e = NULL;
FILE *f = NULL;

e = fopen("test.txt","rb");

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
  printf("\nincorrect unpacking");
  fclose(e);
  fclose(f);
return 0;
} else {

printf("\nsuccessfully unpacked");

}


  fclose(e);
  fclose(f);

return 0;
}
