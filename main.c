#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>

bool pack_file(char *file_a,char *file_b, size_t *len){
FILE *a  = fopen(file_a,"rb");//NULL;
FILE *b = fopen(file_b,"wb");//NULL;

if(!a){

  return 0;
}
if(!b){

  fclose(a);
  return 0;
}

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

    if(buff){
      size_t read = 0;

      while ((read = fscanf(a,"%c",buff)) == 1){

              if(buff[0] & 128){

                fclose(a);
                fclose(b);
                return false;
              }

      for(int i = 1; i < 8 && fscanf(a,"%c",&buff[i]) == 1;i++){
              if(buff[i] & 128){

                fclose(a);
                fclose(b);
                return false;
              }
        read++;
      }

      if(read == 8){
          unsigned char mask = 1;

          for(int j = 1; j < 8; j++){

            if(buff[0] & mask){

              buff[j] = buff[j] | 128;//10000000b
            }

            mask = mask << 1;
          }


        for(int i = 1;i < 8;i++){

          if(fprintf(b,"%c",buff[i]) != 1) {

            fclose(a);
            fclose(b);
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
           }

        }

      }
      }
}

  fclose(a);
  fclose(b);
  free(buff);

  return true;

}
//}
fclose(a);
fclose(b);

return false;
}

bool unpack_file(char *file_a,char *file_b, size_t len){
FILE *a  = fopen(file_a,"rb");//NULL;
FILE *b = fopen(file_b,"wb");//NULL;
//size_t len = 0;


if(!a){

  return 0;
}
if(!b){

  fclose(a);
  return 0;
}
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

      buff[i] = buff[i] & (~mask);
      ix++;
    } else {

      fclose(a);
      fclose(b);
      return false;
    }
  }

  for(int i = 0; i < 8; i++){

    if(fprintf(b,"%c",buff[i]) != 1){

      fclose(a);
      fclose(b);
      return 0;
    }
  }
}
  while(fscanf(a,"%c",buff) == 1){

      if(!fprintf(b,"%c",buff[0])){

        fclose(a);
        fclose(b);
        return 0;
      }
  }

  free(buff);
  fclose(a);
  fclose(b);

  return true;
}

}

fclose(a);
fclose(b);
return false;
}


bool compare(char *file_a,char *file_b){
FILE *a  = fopen(file_a,"rb");//NULL;
FILE *b = fopen(file_b,"rb");//NULL;


if(!a){

  return 0;
}
if(!b){

  fclose(a);
  return 0;
}

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

        fclose(a);
        fclose(b);
        return false;
      }
    } else {

      fclose(a);
      fclose(b);
      return false;
    }
  } else{
    is_end = true;
  }

  }

  fclose(a);
  fclose(b);
  return true;

}

int main()
{
size_t len = 0;
char test1[] = "test.txt";
char test2[] = "test2.txt";
char test3[] = "test3.txt";

if(!pack_file(test1,test2,&len)){

  printf("error packing file");
  return 0;
} else{

  printf("%d",len);
  printf("\nfile packed successfully");
}


if(!unpack_file(test2,test3,len)){

  printf("\nerror unpacking file");
  return 0;
}

if(!compare(test1,test3)){

  printf("\nincorrect unpacking");
  return 0;
} else {

  printf("\nsuccessfully unpacked");
}


return 0;
}
