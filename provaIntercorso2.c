#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>


int fib(int n){
    if(n <= 1)
        return n;
    return fib(n-1)+fib(n-2);
}

int fatt(int n){
    if(n  <= 1)
        return 1;
    return n * fatt(n-1);
}

void handler1(int sig){
    if(sig == SIGINT){
        int temp = 0;
        for(int i = 1; i <= 4; i++){
            temp = temp + fib(i);
        }
        printf("La somma dei primi quattro numeri di Fibonacci è %d\n", temp);
    }
}

void handler2(int sig){
    if(sig== SIGINT){
        char c[20];
        printf("\nVuoi terminare? Premi 'y' per terminare o 'n' per continuare\n");
        scanf("%s", c);

        if(*c == 'y')
            exit(0);
        else
            return;
    }
}

int main(){
    if(signal(SIGINT, SIG_IGN) == SIG_ERR){
        printf("Errore nella signal");
        exit(1);
    }

    pid_t value = fork();
    if(value < 0){
        printf("Errore nella fork\n");
        exit(1);
    }

    if(value == 0){
        if(signal(SIGINT, handler1) == SIG_ERR){
            printf("Errore nella signal\n");
            exit(1);
        }

        for(int i = 1; i <= 30; i++){
            printf("fib(%d): %d\n", i, fib(i)); 
            sleep(1);
        }

        exit(0);
    }

    if(value > 0){
        pid_t value2 = fork();

        if(value2 < 0){
            printf("Errore nella fork\n");
            exit(1);
        }

        if(value2 == 0){
            if(signal(SIGINT, handler2) == SIG_ERR){
                printf("Errore nella signal\n");
                exit(1);
            }

            for(int i = 1; i <= 20; i++){
                printf("fatt(%d): %d\n", i, fib(i));
                sleep(1);
            }

            exit(0);
        }
        else{
            printf("Terminazione figlio con pid %d\n", wait(NULL));
            printf("Terminazione figlio con pid %d\n", wait(NULL));
        }
    }
}