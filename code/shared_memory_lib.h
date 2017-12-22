#ifndef SHARED_MEMORY_LIB_H
#define SHARED_MEMORY_LIB_H

#include <sys/shm.h>


int create_shared_memory(int size){
    return shmget(IPC_PRIVATE, size, 0666);;
}

void remove_shared_memory(int shmid){
    shmctl(shmid, IPC_RMID, NULL);
}


int* attach_shared_memory(int shmid){
    int* memory;
    if((memory = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    return memory;
}


void detach_shared_memory(int *memory_point){
    if(shmdt(memory_point) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
}


#endif // SHARED_MEMORY_LIB_H
