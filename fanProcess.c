#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[])
{

    pid_t processId;
    int numFanProcess = atoi(argv[1]); // number of child argument taken from command line

    printf("Parent Process ID: %d\n", getpid());

    for ( int counter = 0; counter < numFanProcess; counter ++)
    {
        processId = fork();

        if ( processId == 0 )
        {
            printf("Process Number: %d ID: %d Parent ID:%d\n", counter, getpid(), getppid());
            exit(0);
        }
        else
            wait(NULL);
    }

    return 0;
}