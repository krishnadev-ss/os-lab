#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>

int checkprime(int num){
    for(int i = 2; i<=num/2 ; ++i){
        if(num % i == 0){
            return -1;
        }
        
    }
    return 1;
}
int main(){
    int returnstatus;
    int pid;
    int sizepipe[2];
    int arrpipe[2];
    int sizepipe2[2];
    int arrpipe2[2];

    if(pipe(sizepipe)==-1){
        printf("unable to create pipe");
        return -1;
    }

    if(pipe(arrpipe)==-1){
        printf("unable to create pipe");
        return -1;
    }
    if(pipe(sizepipe2)==-1){
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
        close(sizepipe[1]);
        close(arrpipe[1]);
        close(sizepipe2[0]);
        close(arrpipe2[0]);
        int size;
        read(sizepipe[0],&size,sizeof(size));
        int subarr[size];
        read(arrpipe[0],&subarr,sizeof(subarr));
        int prime[size];
        int k= 0;
        for(int i=0;i<size;i++){
            if(checkprime(subarr[i])==1){
                prime[k]=subarr[i];
                k++;
            }
        }

        returnstatus = write(sizepipe2[1],&k,sizeof(k));
        if(returnstatus==-1){
            printf("Error occurred at write of size two");
            return -1;
        }
        returnstatus = write(arrpipe2[1],prime,sizeof(prime));
        if(returnstatus==-1){
            printf("Error occurred at write of size two");
            return -1;
        }
    }
    else{
        close(sizepipe[0]);
        close(arrpipe[0]);
        close(sizepipe2[1]);
        close(arrpipe2[1]);

        int size;
        printf("enter the size of the array:");
        scanf("%d",&size);
        int numarr[size];
        returnstatus = write(sizepipe[1],&size,sizeof(size));
        if(returnstatus == -1){
            printf("error occured");
            return -1;
        }
        printf("enter the elements");
        for(int i=0;i<size;i++){
            scanf("%d",&numarr[i]);
        }
        returnstatus = write(arrpipe[1],numarr,sizeof(numarr));
        if(returnstatus == -1){
            printf("eror occured");
            return -1;
        }
        int size2;
        read(sizepipe2[0],&size2,sizeof(size2));
        int numarr1[size2];
        read(arrpipe2[0],&numarr1,sizeof(numarr1));
        printf("the prime numbers are:");
        for(int i = 0;i<size2;i++){
            printf("%d\n",numarr1[i]);
        }
        wait(NULL);

        }
        return 0;

}