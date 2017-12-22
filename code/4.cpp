//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <time.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/ipc.h>
//#include <sys/sem.h>
//#include <sys/wait.h>
//#include <sys/types.h>
//#include <sys/time.h>
//#include <unistd.h>
//#include <errno.h>
//#include <unistd.h>
//#include <signal.h>
//#include <unistd.h>

//#define MAXSETSIZE 25
//#define PROCESES_LIMIT 10
//#define N_SEMS 1

//void print_time_str(){
//    char fmt[64], buf[64];
//    struct timeval tv;
//    struct tm *tm;
//    gettimeofday(&tv, NULL);
//    if((tm = localtime(&tv.tv_sec)) != NULL)
//    {
//        strftime(fmt, sizeof fmt, "%Y-%m-%d %H:%M:%S. %%06u ", tm);
//        snprintf(buf, sizeof buf, fmt, tv.tv_usec);
//        printf("'%s'", buf);
//    }
//}

//int semaphore_open(){
//    //Фунцкция создаёт множество семафоров
//    return semget(IPC_PRIVATE, N_SEMS, 0777 | IPC_CREAT);
//}

//int semaphore_remove(int sem_id){
//    //Фукнция удаляет семафоры
//    return semctl(sem_id, 0, IPC_RMID, 0);
//}

//int semaphore_decr_op(int semid){
//    //операция декремента семафора
//    struct sembuf semaphore_operation;
//    semaphore_operation.sem_num = 0;
//    semaphore_operation.sem_op = -1;
//    semaphore_operation.sem_flg = 0;
//    return semop(semid, &semaphore_operation, N_SEMS);
//}

//int semaphore_zero_cmp(int semid){
//    //операция проверки на ноль
//    struct sembuf sem_zero_operation;
//    sem_zero_operation.sem_num = 0;
//    sem_zero_operation.sem_op = 0;
//    sem_zero_operation.sem_flg = 0;
//    return semop(semid, &sem_zero_operation, N_SEMS);
//}

//int semaphore_incr_op(int semid){
//    //операция инкремента семафора
//    struct sembuf sem_incr_operation;
//    sem_incr_operation.sem_num = 0;
//    sem_incr_operation.sem_op = 1;
//    sem_incr_operation.sem_flg = 0;
//}

//void worker_process(int semid){
//    int self_pid = getpid();
//    int sleep_time_seconds = self_pid % 10 + 5;
//    int result = 0;
//    while (true){
//        result = semaphore_decr_op(semid);
//        if (result == -1)
//            break;
//        print_time_str();
//        printf("[PID=%d] [RESULT=%d] [WAIT=%d] \n",
//            self_pid, result, sleep_time_seconds);
//        sleep(sleep_time_seconds);
//    }
//    exit(EXIT_SUCCESS);
//}

//int main4()
//{
//    int semid = semaphore_open();

//    for (int i=0; i<PROCESES_LIMIT; i++){
//        if(fork() == 0){
//            printf("Запуск дочернего процесса\n");
//            worker_process(semid);
//        }
//    }

//    int sleep_time = 0;
//    for (int i=0; i<PROCESES_LIMIT; i++){
//        sleep_time = rand() % 4+1;
//        sleep(sleep_time);
//        int result = 0;
//        do {
//            result = semaphore_zero_cmp(semid);
//        }
//        while(result == -1);
//        semaphore_incr_op(semid);
//    }
//    semaphore_remove(semid);
//    while (wait(NULL) > 0) {}
//    return EXIT_SUCCESS;
//}
