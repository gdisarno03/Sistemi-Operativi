#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_usr(int signo){
    if(signo == SIGUSR1)
        printf("Ricevuto SIGUSR1\n");  //per ricevere sigusr1 e sigusr2 fare ./a.out&  poi kill -SIGUSR1 pid
                                    // & serve a eseguire il processo in background in una subshell 
    else if(signo == SIGUSR2)
        printf("Ricevuto SIGUSR2\n");
    else if(signo == SIGINT)
        printf("Ricevuto SIGINT\n");
}


int main(){
    printf("%d\n", getpid());
    if(signal(SIGUSR1, sig_usr) == SIG_ERR){
        printf("Errore sistema: SIGUSR1\n");
        exit(1);
    }

    if(signal(SIGUSR2, sig_usr) == SIG_ERR){
        printf("Errore sistema: SIGUSR2\n");
        exit(1);
    }

    if(signal(SIGINT, sig_usr) == SIG_ERR){
        printf("Errore sistema: SIGINT\n");
        exit(1);
    }

    while(-1) pause();
}