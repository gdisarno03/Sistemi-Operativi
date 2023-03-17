#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


int fatt(int n){
    if(n<2)
        return 1;
    return fatt(n-1)*n;
}

int fib(int n){
    if(n<2)
        return 1;
    return fib(n-1) + fib(n-2);

}

void sig_usr1(int signo){
    if(signo == SIGINT)
        printf("Hai premuto SIGINT (CTRL + C)\nQuesto è il pid del processo: %d\n",getpid());
}

void sig_usr2(int signo){
    if(signo == SIGINT){
        char c[2];
        printf("\rHai premuto SIGINT (CTRL + C)\nDesideri terminare il programma? y/n\n");
        scanf("%c", c);
        
        if (*c == 'y')
            exit(0);        
    }
}

int main(){
    if(signal(SIGINT, SIG_IGN) == SIG_ERR){
        printf("Errore signal figlio1\n");
        exit(1);
    }

    pid_t pid1, pid2;
    pid1 = fork();

    if(pid1 < 0){
        printf("Errore fork 1\n");
        exit(1);
    }
    if(pid1 == 0){
        if(signal(SIGINT, sig_usr1) == SIG_ERR){
            printf("Errore signal figlio1\n");
            exit(1);
        }
        for(int i = 1; i <= 10; i++){
            printf("FIB(%d): %d\n",i, fib(i));
            sleep(1);
        }
        exit(0);    
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
           printf("Errore fork 2\n");
            exit(1);
        }
        if(pid2 == 0){
            if(signal(SIGINT, sig_usr2) == SIG_ERR){
                printf("Errore signal figlio1\n");
                exit(1);
            }
            for(int i = 1; i <= 10; i++){
                printf("FATT(%d): %d\n",i, fatt(i));
                sleep(1);
            }
            exit(0);  
        }
        else{
            wait(NULL);
            wait(NULL);
            printf("figlio1(%d) e figlio2(%d) hanno terminato la loro esecuzione\n", pid1, pid2);
        }
    }
}

