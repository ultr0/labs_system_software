#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

void terminate_handler(int sigtype){
    if (sigtype == SIGUSR1){
        printf("[PID=%d]Caught a terminate signal.\n", getpid());
        alarm(3);
        sleep(12);
    }
    if (sigtype == SIGALRM){
        printf("[PID=%d] End of work\n", getpid());
        raise(SIGKILL);
    }
}

int main(int argc, char *argv[])
{
    int fork_pid = 0;
    int child_pids[7];
    for (int i = 0; i < 7; i++){
        fork_pid = fork();
        if(fork_pid == 0){
            signal(SIGALRM, terminate_handler);
            signal(SIGUSR1, terminate_handler);
            sleep(12);
            return 0;
        }
        child_pids[i] = fork_pid;
    }
    sleep(3);
    for (int i = 0; i < 7; i++){
        kill(child_pids[i], SIGTERM);
    }
    while (wait(NULL) > 0){}\
    printf("End of childs work\n");
    return 0;
}
