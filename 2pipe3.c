#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
//rev strings
void revstr(char *str){
    int temp;
    int len = strlen(str);
    for(int i = 0;i<len/2;i++){
        temp = str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=temp;
    }
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
        int count;
        read(sizepipe[0],&count,sizeof(count));
        char buffer[10][10];
        char revbuffer[10][10];
        read(arrpipe[0],&buffer,sizeof(buffer));
        int temp;

        for(int i=0;i<count;i++){
            revstr(buffer[i]);
            for(int j=0;j<10;j++){
                revbuffer[i][j]=buffer[i][j];
            }
            puts(revbuffer[i]);

        }
  
        

    }
    else{
        close(sizepipe[0]);
        close(arrpipe[0]);
        close(sizepipe2[1]);
        close(arrpipe2[1]);

        int count = 0;
        char c = '\0';
        char buffer[10][10];
        printf("enter the number of names");
        scanf("%d",&count);

        printf("enter nameds:\n");
        for(int i=0;i<count;i++){
            scanf("%s",buffer[i]);
            //printf("%d",strlen(buffer[i]));
        }
        write(sizepipe[1],&count,sizeof(count));
        write(arrpipe[1],buffer,sizeof(buffer));
   
        wait(NULL);

        }
        return 0;

}