#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*Тема  -  Реализация алгоритма сжатия текста.*/

int pack_file(char *file_a,char *file_b){

FILE *a  = fopen(file_a,"rb");
int ret_code = 0;
bool is_ok = true;
if(!a){

  return 1;
}
FILE *b = fopen(file_b,"wb");
if(!b){

  if(fclose(a) != 0){
    return 2;
  }

  return 1;
}
  // fseek(a,0,SEEK_END);
  // int size = ftell(a);
  // fseek(a,0,SEEK_SET);

  size_t ix = 0;

  unsigned char tail = 0;// = size %  8;
 // if(size != 0) {

  if(fprintf(b,"%c",tail) == 1) {

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

    if(buff){
      size_t read = 0;

      while (is_ok == 1){

      for(read = 0; read < 8 && fscanf(a,"%c",(unsigned char*)&buff[read]) == 1 && is_ok;read++){
         if(buff[read] & 128){
            ret_code = 3;
            is_ok = false;

        }
      }

  if(is_ok){
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
            ret_code = 4;
            is_ok = false;
            i = 8;

          }
        }

        }else{
      is_ok = false;

      if(read > 0){

        for(int i = 0; i < read; i++){

          if(fprintf(b,"%c",buff[i]) != 1){
            ret_code = 4;
            is_ok = false;
            i = read;

           }

        }
//is_ok = false;
      fseek(b,0,SEEK_SET);
      fprintf(b,"%c",(char)read);
      }
    }
  }
  ix += read;
}

free(buff);
} else {
  ret_code = 7;
}

}
if(ix == 0) {
//} else {
  ret_code = 10;
}
if(fclose(b) != 0){

  ret_code = 6;
}
if(ret_code && ret_code !=6){
//  if(ix != size){
    remove(file_b);
  //} else {
    // if(ret_code != 10) {
    //   ret_code = 11;
    // }
  //}
}

if(fclose(a) != 0){
  ret_code = 6;
}

return ret_code;
}

int unpack_file(char *file_a,char *file_b){
FILE *a  = fopen(file_a,"rb");//NULL;

bool is_ok = true;
int ret_code = 0;

if(!a){

  return 1;
}
FILE *b = fopen(file_b,"wb");//NULL;
if(!b){

  if(fclose(a) != 0){
    return 2;
  }

  return 1;
}
//if(a && b){
fseek(a,0,SEEK_END);
size_t len = ftell(a);
fseek(a,0,SEEK_SET);

unsigned char tail = 0;
size_t ix = 0;
if(len != 0) {

if(fscanf(a,"%c",(unsigned char*)&tail) == 1){

if(tail < 8 && tail >= 0){

  len = len - (int)tail - 1;

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

  if(buff){

    unsigned char mask = 128;//10000000b

  while(ix < len && is_ok == 1){

  buff[0] = 0;

  for(int i = 1; i < 8/* && is_ok*/; i++){
    if(fscanf(a,"%c",(unsigned char*)&buff[i]) == 1){

      buff[0] = buff[0] | (buff[i] & mask);
      buff[0] = buff[0] >> 1;

      buff[i] = buff[i] & (~mask);
      ix++;
    } else {
      ret_code = 3;
      is_ok = false;
      i = 8;

    }
  }
if(is_ok){
  for(int i = 0; i < 8/* && is_ok*/; i++){

    if(fprintf(b,"%c",buff[i]) != 1){
      ret_code = 4;
      is_ok = false;

    }
  }
}
}
  while(fscanf(a,"%c",buff) == 1 && is_ok){

      if(!fprintf(b,"%c",buff[0])){
        ret_code = 4;
        is_ok = false;

      }
  }

  free(buff);

} else {
ret_code = 5;
}


} else {
ret_code = 9;
}

}
} else {
  ret_code = 7;
}

if(fclose(b) != 0){

  ret_code = 6;
}
if(ret_code && ret_code != 6){
  if(ix != len){
    remove(file_b);
  } else{
  if(ret_code != 7){
    ret_code = 11;
  }
  }
}
if(fclose(a) != 0){
  ret_code = 6;
}

return ret_code;
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

  n1 = fscanf(a,"%c",(unsigned char*)&buf_a);
  n2 = fscanf(b,"%c",(unsigned char*)&buf_b);

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
char text[] = {"\0hello\x1Awo\0rld1234\0q234567"};//"\0helloworld12345\0";
char test1[] = "test01.txt";//"test11.txt";//"test02.txt";//"test03.txt";//"test04.txt";//"test05.txt";//"test06.txt";//"test07.txt";//"test08.txt";
//char test1[] = "test.txt";
char test2[] = "test2.txt";//"test2_10.txt";
char test3[] = "test3.txt";
//  FILE *a = fopen(test1,"w");
//  fwrite(text,1,sizeof(text)-1,a);
// fclose(a);


int code = 0;
if((code = pack_file(test1,test2)) != 0){

  printf("error packing file. code: %d",code);
  return 0;
} else{

  printf("\nfile packed successfully");
}


if((code = unpack_file(test2,test3)) != 0){

  printf("\nerror unpacking file. code: %d",code);
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
