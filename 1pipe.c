#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<time.h>
#include<errno.h>

int main(){
    int returnstatus;
    int pid;


    int sizepipe[2];
    int arrpipe[2];

    if(pipe(sizepipe)==-1){
        printf("unable to create process");
        return -1;

    }
    if(pipe(arrpipe)==-1){
        printf("unable to create pipe");
        return -1;
    }



    pid = fork();


    if(pid == -1){
        printf("process not created");
        return -1;
    }


    if(pid == 0){
        close(sizepipe[1]);
        close(arrpipe[1]);
        int size;
        read(sizepipe[0],&size,sizeof(size));
        int subarr[size];
        read(arrpipe[0],&subarr,sizeof(subarr));
        int sum = 0;
        for(int i = 0;i<size;i++){
            sum+=subarr[i];
        }
        printf("the sum is %d",sum);
        
    }
    else{
        close(sizepipe[0]);
        close(arrpipe[0]);
        int size;
        printf("enter the number of elemeenst in the array");
        scanf("%d",&size);
        int numarr[size];
        returnstatus = write(sizepipe[1],&size,sizeof(size));
        if(returnstatus == -1){
            printf("error occcured");
            return -1;

        }
        printf("enter the number to add:");
        for(int i = 0;i<size;i++){
            scanf("%d",&numarr[i]);
        }
        returnstatus = write(arrpipe[1],numarr,sizeof(numarr));
        if(returnstatus == -1){
            printf("error occured");
            return -1;
        }
        wait(NULL);
    }
    return 0;
}