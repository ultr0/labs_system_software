# include <iostream>
# include <cstdlib>
# include <ctime>
# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h># include <signal.h># include <unistd.h>using
namespace
std;int
main()
{

    srand(time(0));
int
par = getpid();
pid_t
pid;
char
buf[255] = "Etot text peredan papoi sinu";
char
buff[255];
int
fd[2];
pipe(fd);
// cin >> buf;
// cout << endl;
pid = fork();
if (getpid() == par)

{

    write(fd[1], & buf, 10

    // sizeof(buf)

);
}

if (getpid() != par)

{

cout << "Create. Child ID= " << getpid() << ". Parent ID= " << par << endl;
// sleep(1);
read(fd[0], & buff, 10

// sizeof(buf)

);
buff[10]='\0';
if (buff != NULL)

cout << buff << endl;
else

cout << "NIRABOTAET" << endl;
sleep(1);
}

waitpid(pid, 0, 0);
if (getpid() == par)

cout << "Ya zakonchil rabotu." << endl;
return 0;
}
