#ifndef SEMAPHORE_LIB_H
#define SEMAPHORE_LIB_H

#include <sys/sem.h>

#define N_SEMS 1

int semaphore_open(){
    // Функция создает множесто семафоров
    // В множестве будет только один семафор (нам больше и не нужно)
    return semget(IPC_PRIVATE, N_SEMS, 0666 | IPC_CREAT);
}


int semaphore_remove(int sem_id){
    // Функция удаляет множество семафоров
   return semctl(sem_id, 0, IPC_RMID, 0);
}


int semaphore_decr_op(int semid){
    // Операция декремента семафора
    struct sembuf semaphore_operation;
    semaphore_operation.sem_num = 0;
    semaphore_operation.sem_op = -1;
    semaphore_operation.sem_flg = 0;
    return semop(semid, &semaphore_operation, N_SEMS);
}


int semaphore_zero_cmp(int semid){
    // Операция проверки на ноль
    struct sembuf sem_zero_operation;
    sem_zero_operation.sem_num = 0;
    sem_zero_operation.sem_op = 0;
    sem_zero_operation.sem_flg = 0;
    return semop(semid, &sem_zero_operation, N_SEMS);
}


int sempaphore_incr_op(int semid){
    //Операция инкремента семафора
    struct sembuf sem_incr_operation;
    sem_incr_operation.sem_num = 0;
    sem_incr_operation.sem_op = 1;
    sem_incr_operation.sem_flg = 0;
    return semop(semid, &sem_incr_operation, N_SEMS);
}


#endif // SEMAPHORE_LIB_H
