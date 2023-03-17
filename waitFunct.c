#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


int main(){
    pid_t value = fork();
    int status;

    if(value < 0)
        printf("Errore nella chiamata fork()");

    if(value == 0){
        printf("Sono figlio con pid : %d\n", getpid());
        exit(0);
    }
    else{
        value = wait(&status);
        if(WIFEXITED(status))
            printf("Terminazione volontaria di %d con stato %d\n", value, WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
            printf("Terminazione involontaria per segnale %d\n", WTERMSIG(status));
    }

}