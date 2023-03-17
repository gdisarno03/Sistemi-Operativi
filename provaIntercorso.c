#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


int main(){
    pid_t value1 = fork();
    int status;

    if(value1 < 0){
        printf("Errore nella chiamata fork()\n");
        exit(1);
    }

    if(value1 == 0){
        printf("Pid primo figlio : %d\n", getpid());
        for(int i = 1; i <= 50; i++)
            printf("%d\n", i);
        exit(0);
    }

    if(value1 > 0){
        pid_t value2 = fork();

        if(value2 < 0){
            printf("Errore nella chiamata fork()\n");
            exit(1);
        }

        if(value2 == 0){
            printf("Pid processo padre : %d\n", getppid());
            execl("/bin/ls", "ls", (char*)0);
            exit(0);
        }

        if(value2 > 0){
            printf("Terminazione figlio con pid : %d\n", wait(&status));
            printf("Terminazione figlio con pid : %d\n", wait(&status));
        }
    }
}