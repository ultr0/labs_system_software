#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h> //библиотека для расчёта времени

int main(int argc, char *argv[])
{
    int fork_pid = 0;
    int child_pids[7];
    for (int i=0; i<7; i++){
        fork_pid = fork();
        if (fork_pid == 0){
            int timeout = (rand() + getpid()) % 10;
            sleep(timeout);
            printf("PID потомка: %d %d\n", getpid(), rand()%10);
            exit(0);
        }
        child_pids[i] = fork_pid;
    }
    time_t timer;
    time(&timer);
    double seconds;
    while (wait(NULL) > 0){
        seconds = difftime(time(NULL), timer);
        if (seconds > 30){
            for (int i=0; i<7; i++){
                kill(child_pids[i], SIGKILL);
            }
        }
    }
    printf("Работа процессов потомков завершена! \n");
    return 0;
}
