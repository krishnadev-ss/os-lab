#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>

int main(){
    int returnstatus;
    int pid;
    
    int arrpipe[2];
 
    int arrpipe2[2];


    if(pipe(arrpipe)==-1){
        printf("unable to create pipe");
        return -1;
    }
    
    if(pipe(arrpipe2)==-1){
        printf("unable to create pipe");
        return -1;
    }

    pid = fork();


    if(pid==-1){
        printf("process not created");
        return -1;
    }

    if(pid == 0){
        
        close(arrpipe[1]);
       
        close(arrpipe2[0]);
        char buffer[10];
        int palindrome = 1;
        read(arrpipe[0],&buffer,sizeof(buffer));
        int len = strlen(buffer);
        for(int i =0;i<len/2;i++){
            if(tolower(buffer[i])!=tolower(buffer[len-i-1])){
                palindrome = 0;
                break;
            }
            palindrome = 1;
        }
       

        returnstatus = write(arrpipe2[1],&palindrome,sizeof(palindrome));
        if(returnstatus==-1){
            printf("Error occurred at write of size two");
            return -1;
        }
    }
    else{
      
        close(arrpipe[0]);
      
        close(arrpipe2[1]);

        char buffer[10];
        printf("enter the string:");
        scanf("%s",buffer);

     
        

        returnstatus = write(arrpipe[1],buffer,sizeof(buffer));
        if(returnstatus == -1){
            printf("eror occured");
            return -1;
        }
        int palindrome;
        read(arrpipe2[0],&palindrome,sizeof(palindrome));
        if(palindrome == 1){
            printf("string is palindrome");
        }
        else{
            printf("string is not palindrome");
        }
       
        wait(NULL);

        }
        return 0;

}