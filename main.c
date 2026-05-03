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
        read++;
      }
if(read == 8){//printf("%s",buff);
          unsigned char mask = 1;

          for(int j = 1; j < 8; j++){

            if(buff[0] & mask){

              if(buff[j] & 128){
//printf("%s",buff);
                return false;
              }

              buff[j] = buff[j] | 128;//10000000b
            }

            mask = mask << 1;
          }

          // if(!fwrite(&buff[1],1,7,b)){
          // // if(!fprintf(b,"%7c",&buff[1])) {
          // //   return false;
          //    }

        for(int i = 1;i<8;i++){

          if(!fprintf(b,"%c",buff[i])) {
            return false;
          }else{
            (*len)++;
          }
        }
        //*len += 7;
        }else{
      if(read > 0){

        if(!fwrite(buff,1,read,b)){

          return false;
        }else{
          *len++;
        }
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

    size_t read = 0;
    size_t read_total = 0;
    size_t remain = len % 8;
    size_t len_8 = len - remain;//(len%8);
    size_t ix = 0;
while(ix < len){    buff[0] = 0;
  for(int i = 1; i < 8; i++){
if(fscanf(a,"%c",&buff[i]) == 1){

    unsigned char mask = 128;//10000000b
    buff[0] = buff[0] | (buff[i] & mask);
    buff[0] = buff[0] >> 1;
printf(" %d",buff[0]);
    buff[i] = buff[i] & (~mask);
    ix++;
}else{

return false;
}
  }

  for(int i = 0; i < 8; i++){
    if(!fprintf(b,"%c",buff[i])){
      return 0;
    }
  }
}
while(fscanf(a,"%c",buff) == 1){
    if(!fprintf(b,"%c",buff[0])){
      return 0;
    }
}
// for(int i = 0; i <remain; i++){
//   if(fscanf(a,"%c",&buff[i]) != 1){
// return false;
// }
//     if(!fprintf(b,"%c",buff[i])){
//       return 0;
//     }
// }
//return 1;
//delay cherez absolutniy index ix!!!!!!!!!
  //   while((read = fscanf(a,"%c",&buff[1])) == 1 && read_total < len){

  //     buff[0] = 0;
  //     unsigned char mask = 128;

  //     for(int i = 1; i < 8; i++){

  //       buff[0] = buff[0] | (buff[i] & mask);
  //       buff[0] = buff[0] >> 1;

  //       buff[i] = buff[i] & (~mask);

  //     }


  //     if(!fwrite(buff,1,8,b)){
  //       return false;
  //     }
  //     read_total += 7;

  //   }

  //   if(read > 0){

  //     if(!fwrite(&buff[1],1,read,b)){

  //       return false;
  //     }
  //   }

  // return true;
  // }

return true;
}

return false;
}
return false;
}


bool compare(FILE *a, FILE *b){

if(a && b){
  unsigned char buf_a = 0;
  unsigned char buf_b = 0;

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
