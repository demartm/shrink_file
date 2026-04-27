#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *a;
a = fopen("/home/root_user/shrink_file/main.c","r");
char *buff = (char*)calloc(100,sizeof(char));
if(a){

while(fread(buff,1,1,a) > 0){
printf("1");
}

}
 //   printf("Hello World!\n");
    return 0;
}
