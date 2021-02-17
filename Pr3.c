#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define SIZE 20
#define COUNTSIZE 26

void findOccrences(char str1[],char str2[],int *counter);

int main(){
char first_string[SIZE];
char second_string[SIZE];
char op;
int *counter = (int*) malloc(COUNTSIZE*sizeof(int));
int i;


printf("Enter strings and a operator:\n");
scanf("%s %c %s",first_string,&op,second_string);
printf("%s %c %s\n",first_string,op,second_string);

findOccrences(first_string,second_string,counter);

for(i = 0; i<COUNTSIZE;i++){
printf("%d ",counter[i]);

}

return 0;


}

void findOccrences(char str1[],char str2[],int *counter){
char a = 'a';
int i;

for(i = 0; i<strlen(str1);i++){
int index = str1[i] -a;
counter[index]+=1; 

}


for(i = 0; i<strlen(str2);i++){
int index = str2[i] -a;
counter[index]+=1; 

}

}
