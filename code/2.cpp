#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
using namespace std;
void AA(int c4){
    sleep(3);
    cout<<"Уничтожение процессов"<<endl;
    exit(0);
}

int main2()
{
    srand(time(0));
    int par=getpid();
    pid_t pid;
    int CPid=0;
    int CRan=0;
    int mx=0;
    int mxp=0;
    for(int i=0; i<7; i++){
        int ran = 3+rand()%10;

        pid=fork();

       if(getpid()!=par)
           cout<<"Создание. Child ID= "<<getpid()<<". Time= "<<ran<<". Parent ID= "<<par<<endl;

       CPid=getpid();
       CRan=ran;

       if(getpid()!=par) break;

       if(mx<ran){
           mx=ran;
           mxp=pid;
       }
    }

   if(getpid()!=par) {
        sleep(CRan);
        cout<<"Ожидание. Child ID= "<<CPid<<". Time= "<<CRan<<". Parent ID= "<<par<<endl;
    }


  if(getpid()!=par) {
      struct sigaction act;
      act.sa_handler = AA;
      sigset_t   set;
      sigemptyset(&set);
      sigaddset(&set, SIGUSR1);
      act.sa_mask = set;
      sigaction(SIGUSR1, &act, 0);
  }
 waitpid(mxp,0,0);
 if(getpid()!=par)
     kill(getpid(),SIGUSR1);
     cout<<"Все дочерние процессы завершены."<<endl;
    return 0;
}

