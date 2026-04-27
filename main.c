#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{

FILE *a, *b;
a= fopen("test.txt","rb");
b= fopen("test3.txt","rb");

unsigned char buf_a = 0;
unsigned char buf_b = 0;

bool is_end =false;

while(fread(&buf_a,1,1,a) && fread(&buf_b,1,1,b) && !is_end){
  if(buf_a != buf_b){
    printf("error");
    is_end = true;
  }
}
fclose(a);
fclose(b);

    return 0;
}
