#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> //библиотека ожидания системных процессов
#include <signal.h>
#include <time.h> //библиотека для расчёта времени

int main1(int argc, char *argv[])
{
    int fork_pid = 0;
    int child_pids[7];
    for (int i=0; i<7; i++){
        fork_pid = fork(); //создание потомка
        sleep(rand()%7 + 3); //задержка от 3 до 10 секунд
        if (fork_pid == 0){
            printf("PID потомка: %d\n", getpid());
            exit(0); //оповещение
        }
        child_pids[i] = fork_pid;
        int u = kill(child_pids[i], SIGKILL);
        printf("PID завершённого потомка: %d, %d\n", child_pids[i], u);
    }
    time_t timer;
    time(&timer);
    double seconds;
    while (wait(NULL) > 0){
        seconds = difftime(time(NULL), timer);
        if (seconds > 30){
            for (int i=0; i<7; i++){
                kill(child_pids[i], SIGKILL);
                printf("PID завершённого потомка: %d\n", child_pids[i]);
            }
        }
    }
    printf("Работа процессов потомков завершена! \n");
    return 0;
}
