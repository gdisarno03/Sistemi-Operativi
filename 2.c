        #include <stdio.h>
        #include <unistd.h>
        #include <stdlib.h>
        #include <time.h>
        #include <sys/types.h>
        #include <sys/wait.h>
        #include <signal.h>

        int fib(int n){
            if(n<2)
                return 1;
            return fib(n-1) + fib(n-2);

        }

        void sig_usr(int signo){
            signal(SIGINT, SIG_IGN);
            if(signo == SIGINT){
                pid_t value2 = fork();

                if(value2 == 0){
                    char c[2];
                    printf("Hai premeuto SIGINT (CTRL+C). Vuoi terminare il processo padre F?\n");

                    if(*c == 'y'){
                        kill(getppid(), 9);
                        raise(9);
                    }
                    exit(0);      
                }
            }
        }


        int main(){
            pid_t value1 = fork();

            if(value1 < 0)
                printf("Errore nella fork\n");
            
            if(value1 == 0){
                if(signal(SIGINT, sig_usr) == SIG_ERR){
                    printf("Errore signal figlio1\n");
                    exit(1);
                }

                for(int i = 1; i <= 10; i++){
                    printf("FIB(%d)\n", fib(i));
                    sleep(2);
                }
                exit(0);
            }

            if(value1 > 0){ 
                if(signal(SIGINT, SIG_IGN) == SIG_ERR){
                    printf("Errore signal padre\n");
                    exit(1);
                }

                printf("Terminazione figlio con pid: %d\n", wait(NULL));
            }

        }