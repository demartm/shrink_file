#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

FILE *a, *b;
a= fopen("test.txt","rb");
b= fopen("test3.txt","rb");

if(!compare(a,b)){
printf("error");
}

    return 0;

}
