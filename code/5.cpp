#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#include <semaphore_lib.h>
#include <shared_memory_lib.h>

#define MAXSETSIZE 25
#define PROCESES_LIMIT 10
#define N_SEMS 1


void print_time_str(){
    char            fmt[64], buf[64];
    struct timeval  tv;
    struct tm       *tm;
    gettimeofday(&tv, NULL);
    if((tm = localtime(&tv.tv_sec)) != NULL)
    {
        strftime(fmt, sizeof fmt, "%Y-%m-%d %H:%M:%S.%%06u ", tm);
        snprintf(buf, sizeof buf, fmt, tv.tv_usec);
        printf("'%s'", buf);
    }
}

void print_data_array(int *array){
    printf("PROCESS_INDEX | DATA\n");
    for (int pindex = 0; pindex < PROCESES_LIMIT; pindex++){
        printf("%13d | %4d\n", pindex, array[pindex]);
    }
}

int get_sum(int* array, int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += array[i];
    }
    return sum;
}

void worker_process(int pindex, int shmid, int semid){
    int self_pid = getpid();
    int process_weight = self_pid % 5 + 1;
    int result = 0;

    // Разделяемая память
    int* memory_array;

    result = semaphore_decr_op(semid);
    if (result == -1)
        exit(EXIT_SUCCESS);

    // Присоединяем общую память
    memory_array = attach_shared_memory(shmid);

    print_time_str();
    printf("\n\n[PID=%d][RES=%d][WAIT=%d]\n",
           self_pid, result,process_weight);

    int new_value = get_sum(memory_array, PROCESES_LIMIT);

    if (new_value == 0) new_value = 1;

    memory_array[pindex] = new_value;
    print_data_array(memory_array);

    // Отсоединяем общую память
    detach_shared_memory(memory_array);
    exit(EXIT_SUCCESS);
}


int main()
{
    int semid = semaphore_open();

    // Созаем общую область памяти
    int shmid = create_shared_memory(PROCESES_LIMIT*sizeof(int));

    for (int pindex = 0;  pindex < PROCESES_LIMIT; pindex++){
        if(fork() == 0){
            printf("Запускаем дочерний процесс\n");
            worker_process(pindex, shmid, semid);
        }
    }

    int* memory_array = attach_shared_memory(shmid);
    int sleep_time = 0;

    for (int pindex = 0;  pindex < PROCESES_LIMIT; pindex++){
        sleep_time = rand() % 4 + 1;
        sleep(sleep_time);
        int result = 0;
        do {
            result = semaphore_zero_cmp(semid);
        } while(result == -1);
        sempaphore_incr_op(semid);
    }

    detach_shared_memory(memory_array);

    // Уничтожаем общую область памяти
    remove_shared_memory(shmid);

    semaphore_remove(semid);

    while (wait(NULL) > 0){}

    return EXIT_SUCCESS;
}

