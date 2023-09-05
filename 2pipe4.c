#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int isFibonacci(int data) {
    int num1 = 0, num2 = 1, temp, flag = 0;

    if (data == num1 || data == num2) {
        return 1;
    }

    while (num2+num1 <= data) {
        temp = num2;
        num2 = num1 + num2;
        num1 = temp;
        if (num2 == data) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int pipe1[2], pipe2[2], pipe3[2]; 
    int pid1, pid2;

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3); 

    pid1 = fork();
    if (pid1 == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        int num;
        int fact = 1;
        read(pipe1[0], &num, sizeof(num));
        for (int i = 1; i <= num; i++) {
            fact *= i;
        }
        printf("factorial of %d is %d\n", num, fact);
        write(pipe2[1], &fact, sizeof(fact));
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            close(pipe2[1]);
            close(pipe3[0]);
            int fact, flag;
            int arr[30]; // Fixed size for the array
            //memset(arr, 0, sizeof(arr)); // Initialize the array to 0
            int index = 0;
            read(pipe2[0], &fact, sizeof(fact));
            printf("non fibonacci series upto %d term are:\n", fact);
            for (int i = 1; i <= fact; i++) {
                flag = isFibonacci(i);
                if (!flag) {
                    arr[index] = i;
                    index++;
                }
            }
            write(pipe3[1], arr, sizeof(arr)); 
        } else {
            close(pipe1[0]);
            close(pipe3[1]);
            int num;
            printf("enter the number to find factorial:");
            scanf("%d", &num);
            write(pipe1[1], &num, sizeof(num));
            int arr[30];
            read(pipe3[0], arr, sizeof(arr));
            size_t size = sizeof(arr) / sizeof(arr[0]);
            //int size = strlen(arr)+1;
           
             // Calculate the actual size
            for (int i = 0; i < size; i++) {
                if (arr[i] != 0) { // Avoid printing uninitialized elements
                    printf("%d\n", arr[i]);
                }
            }
            wait(NULL);
        }
    }
    return 0;
}
