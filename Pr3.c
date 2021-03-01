//Name: Zheng Zhong, OS: Unbutun 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>


#define STRSIZE 128
#define COUNTSIZE 26
#define OPSIZE 2
#define ADDOP '+'
#define MUTOP 'x'

int checkInputString(char str[]);
int* addition(char str1[],char str2[]);
int* mutiply(char str1[],char str2[]);
void findOccrences(char str1[],char str2[],int *counter);
void printCounter(int *counter);
int* rearrange(unsigned long sum);
int  countersSum(int *counter);
char* getNewString(int *counter);
void upToLow(char str[]);

//Main function 
//pre: Command Line argument size: inputSize ,and Command Line agrument array:args[];
//post:Sum or product of two strings

int main(int inputSize,char*args[]){

    //Varaibles setup: 
    //first_string and second_string store the input strings
    //op stores the operator character
    //InvalInput stores the invaild input information
    //newString stores the new string resulted from the two input string;
    char first_string[STRSIZE],second_string[STRSIZE], op[OPSIZE],invalInput,*newString;
    int i,s1,s2;
    int *counter = (int*) calloc(COUNTSIZE,sizeof(int));

    if(inputSize<4){
       printf("Invalid number of arguments\n");
    }

    else{
         //Copies the strings and operator from command line argument to corresponding variables
         strcpy(first_string,args[1]);
         strcpy(op,args[2]);
         strcpy(second_string,args[3]);
         upToLow(first_string);
         upToLow(second_string);

         //checkInput function dectects invalid operand,return 1 if the string is an invalid operand
         //If the sum of two invalInputs is 1, then there is/are invaild operand(s), else 0
         invalInput= checkInputString(first_string);
         invalInput+= checkInputString(second_string);


        if(invalInput==0){
 

            switch(op[0]){
             
              //If the operator is '+', then perfoms addition operation.
              case ADDOP :
                    counter = addition(first_string,second_string); 
                    newString = getNewString(counter);
                    printf("%s %s %s => %s\n",first_string,op,second_string,newString);
                    break;
              //If the operator is 'x', then perfoms mutiplication operation.
              case MUTOP:
                    counter = mutiply(first_string,second_string);
                    newString = getNewString(counter);
                    printf("%s %s %s => %s\n",first_string,op,second_string,newString);
                    break;
              //If the operator is other character, then prints 'invalid operator' error message.
              default : 
                    puts("invalid operator\n");}
   
              
        }
        else{
             //If one of the operands is no valid, print out "invalid operand" error message.
              printf("invalid operand\n");
         

        }


    }
       
  free(counter);
  printf("------------\n");
  return 0;


}
//Checks the input string validity
//pre: input string: str
//post: a integer reprsents the string validity, 0 means input strings is valid, else invalid.

int checkInputString(char str[]){

  char a ='a', z='z';
  int i,valid = 0;
  for(i = 0 ; i<strlen(str) ; i++){
     if(str[i]< a || str[i] > z ){
          valid =1;
          break;

     }

  } 
    
   return valid;

}

//Addition adds two strings to get a new string counter array by using John Napier's location arithmetic
//pre: the first string:str1 and the second string: str2
//post:a counter array filled with letter occrences for the new string

int* addition(char str1[],char str2[]){

    int *oldCounter = (int*) calloc(COUNTSIZE,sizeof(int)),*newCounter = (int*) calloc(COUNTSIZE,sizeof(int));
    unsigned long sum = 0;
 
    //function findOccrences calculates the letter occurence from the two input strings
    findOccrences(str1,str2,oldCounter);
    
    //function countersSum results the sum of letter occrences counter array
    sum = countersSum(oldCounter);

    //function rearrange results a new counter array for the new string
    newCounter = rearrange(sum);

    free(oldCounter);
    return newCounter;


}

//One string mutiplies by another string to get a new string counter array by using John Napier's location arithmetic
//pre: the first string:str1 and the second string: str2
//post:a counter array filled with letter occrences for the new string
int* mutiply(char str1[],char str2[]){

       int *counter = (int*) calloc(COUNTSIZE,sizeof(int));
       int i, j,total;
       unsigned long product=0;
       char a = 'a',addend1,addend2;
   
      //Get the product of letters' digits
       for(i = 0 ; i<strlen(str1);i++){
         
          addend1 = str1[i]-a;
          total = 0;
          
          for( j =0;j<strlen(str2);j++){
         
              addend2 = str2[j]-a;
              total+=pow(2,addend1+addend2);
  
          } 
  
          product +=total;
       }


       counter = rearrange(product);


       return counter;  


 }




//Calculates the letter occurrence from two input strings, then stores the result into a counter array
//pre:first string: str1, second string:str2, the counter array:counter
//post:a counter array filled letter occurences
void findOccrences(char str1[],char str2[],int *counter){

     char a = 'a';
     int i,index;

     for(i = 0; i<strlen(str1);i++){
        
         index = str1[i] -a;
         counter[index]+=1;

     }

     for(i = 0; i<strlen(str2);i++){
      
         index = str2[i] -a;
         counter[index]+=1;

    }
}



//Prints the counter array
//pre:the counter array:counter
//post:no
void printCounter(int *counter){

      int i;

      for(i = 0; i<COUNTSIZE;i++){
          
          printf("%d ",counter[i]);

      }

       printf("\n");

}


//Gets the sum of the letters' digits
//pre:the counter array:counter
//post:the sum of letters's digits

int  countersSum(int *counter){

     int i,time,sum=0;

     for(i=0 ; i<COUNTSIZE ; i++){
        
        time = counter[i];
        sum += time*pow(2,i);

     }

     return sum;

}

//Gets the new counter array 
//pre:sum of the previous counter array
//post:the rearranged counter array from the old counter array

int* rearrange(unsigned long sum){
      int index,dif;
      unsigned long rem=sum;
      int *newCounter = calloc(COUNTSIZE,sizeof(int));
      index = COUNTSIZE-1;

      while(rem>0){
           
           dif = rem - pow(2,index);
      
           if(dif>=0){
      

             newCounter[index]+=1;
             rem = dif;
             continue;

           }
 
          index--;

    }

     return newCounter;
}


//Generates a new string from the new counter array
//pre: the new counter array : counter
//post: a char pointer point to the new string
char* getNewString(int *counter){

      char *newString = malloc(STRSIZE*sizeof(char));
      char a = 'a',letter;
      int i ,time,index=0;

      for(i = 0; i<COUNTSIZE;i++){
 
         time = counter[i];
         
         while(time>0){
      
             letter = i+a;
             newString[index]= letter;  

             index++;
             time--; 

          }



      } 



      return newString;

}

//Converts upper case letter to lower case letter in a string
//pre:the input string: str
//post: the input string now filled with lower case letters
void upToLow(char str[]){
  
     int i;
   
     for(i = 0;i<strlen(str);i++){
        
         str[i]=tolower(str[i]);
       

     }
     

}




