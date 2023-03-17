#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>


void sig_usr(int signo){
    if(signo == SIGINT){
        char c;
        printf("\rHai premuto SIGINT (CTRL + C)\nDesideri terminare il programma? y/n\n");
        scanf("%c", &c);
        getchar();
        if (c == 'y')
            exit(0);
        
    }
}

int main(){
    signal(SIGINT, sig_usr);
    for(int i = 1; i <= 10; i++){
        printf("%d\n", i);
        sleep(1);
    }
    while(-1)
        pause();//ciclo utile se arriviamo alla fine del for. Il programma dovrà sempre attender eil segnale per arrestarsi
}