#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*Тема  -  Реализация алгоритма сжатия текста.*/
int pack_file(char *file_a, char *file_b){

if(file_a && file_b){

FILE *a  = fopen(file_a,"rb");

int ret_code = 0;

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

char read = 0;
unsigned char tail = 0;
if(fprintf(b,"%c",tail) == 1){

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

  if(buff){

  int status = 1;

    while(status == 1 && ret_code == 0){
     read = 0;
    for(int i = 0; i < 8; i++) {


    if((status = fscanf(a,"%c",(unsigned char*)&buff[i])) == 1){

      if(buff[i] & 128){
        i = 8;
        ret_code = 3;
      }
      read++;

    } else {
      i = 8;
    }
  }

    if(ret_code == 0){
      if(read == 8){
          unsigned char mask = 1;

          for(int j = 1; j < 8; j++){

            if(buff[0] & mask){

              buff[j] = buff[j] | 128;//10000000b
            }

            if(fprintf(b,"%c",buff[j]) != 1){
              ret_code = 4;
              j = 8;
            }

            mask = mask << 1;
          }
      } else {
        if(read > 0){
          tail = read;
          for(int i = 0; i < read; i++){
            if(fprintf(b,"%c",buff[i]) != 1){
              ret_code = 4;
              i = read;
            }
          }
        }
      }
    }

  }

if(ret_code == 0){
  if(fseek(b,0,SEEK_SET) != 0){
    ret_code = 6;
  } else {

    if(fprintf(b,"%c",tail) != 1){
      ret_code = 6;
    }
  }
}

free(buff);
  } else {
    ret_code = 7;
  }

}else {
    ret_code = 8;
  }


if(fclose(b) != 0){
 ret_code = 9;
} else {
  if(ret_code && ret_code != 9){
    if(remove(file_b) != 0){
      ret_code = 10;
    }
  }
}

if(fclose(a) != 0) {
  ret_code = 9;
}


return ret_code;

} else {
 return -1;
}

}

int unpack_file(char *file_a,char *file_b){
if(file_a && file_b){
FILE *a  = fopen(file_a,"rb");

int ret_code = 0;

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

char test = 0;

unsigned char tail = 0;

if(fscanf(a,"%c",(unsigned char*)&tail) == 1){

if(tail < 8){

  unsigned char *buff = (unsigned char*)calloc(8,sizeof(unsigned char));

  if(buff){

  unsigned char mask = 128;//10000000b
  int status = 1;
  while(status == 1 && ret_code == 0){

  buff[0] = 0;

  unsigned char read = 0;
  for(int i = 1; i < 8; i++){
    if((status = fscanf(a,"%c",(unsigned char*)&buff[i])) == 1){
      read++;
    }
  }

if(read == 7){

if(read == tail && fscanf(a,"%c",&test) != 1){
    for(int i = 1; i < 8; i++){
      if(fprintf(b,"%c",buff[i]) != 1) {
        i = 8;//read + 1;
        ret_code = 5;
      }
    }


} else {
    if(read == tail){
      fseek(a,-1,SEEK_CUR);
    }
    for(int i = 1; i < 8; i++){
      buff[0] = buff[0] | (buff[i] & mask);
      buff[0] = buff[0] >> 1;

      buff[i] = buff[i] & (~mask);
    }


    for(int i = 0; i < 8; i++){
      if(fprintf(b,"%c",buff[i]) != 1) {
        i = 8;
        ret_code = 4;
      }
    }

}


} else {
    for(int i = 1; i <= read; i++){
      if(fprintf(b,"%c",buff[i]) != 1) {
        i = read + 1;
        ret_code = 5;
      }
    }
}
}
free(buff);
} else {
  ret_code = 9;
}
} else {
  ret_code = 8;
}
}


  if(fclose(b) != 0){
    ret_code = 6;
  } else {
if(ret_code && ret_code != 6){
  if(remove(file_b) != 0){
    ret_code = 7;
  }
}

  }
  if(fclose(a) != 0){
    ret_code = 6;

  }

return ret_code;
}
return -1;
}
bool compare(char *file_a,char *file_b,int *code){
if(file_a && file_b && code){
FILE *a  = fopen(file_a,"rb");//NULL;
FILE *b = fopen(file_b,"rb");//NULL;


if(!a){
  *code = 1;
  return 0;
}
if(!b){
  *code = 1;
if(fclose(a) != 0){

  *code = 2;
}
  return 0;
}

  unsigned char buf_a = 0;
  unsigned char buf_b = 0;
  int n1 = 0;
  int n2 = 0;

  bool same = true;

  while(n1 == 1 && n2 == 1 && same == true){
    n1 = fscanf(a,"%c",&buf_a);
    n2 = fscanf(b,"%c",&buf_b);
    if((unsigned char)buf_a != (unsigned char)buf_b){
      same = false;
    }
  }
  if(n1 == 1 || n2 == 1){
    same = false;
  }

  if(fclose(a) != 0){
    *code = 3;
  }

  if(fclose(b) != 0){
    *code = 4;
  }

  return same;
}
return false;
}


int main()
{
char text[] = {"\0hello\x1Awo\0rld1234\0q234567"};//"\0helloworld12345\0";
char test1[] = "test01.txt";//"test11.txt";//"test02.txt";//"test03.txt";//"test04.txt";//"test05.txt";//"test06.txt";//"test07.txt";//"test08.txt";
//char test1[] = "test.txt";
char test2[] = "test2.txt";//"test2_10.txt";
char test3[] = "test3.txt";
//  FILE *a = fopen(test1,"w");

// for(int i = 0; i < sizeof(text); i++){
//   fprintf(a,"%c",text[i]);
// }

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

if(!compare(test1,test3,&code)){

  printf("\nincorrect unpacking");
  return 0;
} else {

  printf("\nsuccessfully unpacked");
}


return 0;
}
