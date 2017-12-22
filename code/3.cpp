# include <iostream>
# include <cstdlib>
# include <ctime>
# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
using namespace std;
int main3()
{
    srand(time(0));
    int par = getpid();
    pid_t pid;
    char buf[255] = "Данные для канала данных.";
    char buff[255];
    int fd[2];
    pipe(fd);
//    cin >> buf;
//    cout << endl;
    pid = fork();
    if (getpid() == par)
    {
        write(fd[1], & buf, 50
//                 sizeof(buf)
                );
    }
    if (getpid() != par)
    {
//        for(int i=0; i<7; i++){
        cout << "Создание дочернего процесса c PID= " << getpid() << ". Родительский PID= " << par << endl;
        // sleep(1);
        read(fd[0], & buff, 50
                // sizeof(buf)
                );
//        buff[12]='\n';
        if (buff != NULL)
            cout << buff << endl;
        else
            cout << "Ошибка." << endl;
        sleep(1);\
//    }
    }
    waitpid(pid, 0, 0);

    if (getpid() == par)

        cout << "Завершение работы." << endl;
    return 0;
}
