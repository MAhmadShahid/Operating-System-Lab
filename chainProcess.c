#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>


void createChainProcess(int numberOfProcess) // iteratively makes chain processes
{
    int counter = 0;
        
    printf("Process Number: %d ID: %d Parent ID:%d\n", counter, getpid(), getppid());
    
    while(counter < numberOfProcess)
    {
        pid_t pid = fork();
        
        counter ++;
    
        if (pid == 0)
        {
            printf("Process Number: %d ID: %d Parent ID:%d\n", counter, getpid(), getppid());
        }
        else
        {
            wait(NULL);
            break;
        }
    }

    exit(0);

}

void createChainProcessR(int numberOfProcess) // recursively makes chain process
{
    if ( numberOfProcess <= 0)
        return;

    pid_t pid = fork();


    if ( pid == 0 )
    {
        printf("Process ID: %d Parent ID:%d\n", getpid(), getppid());
        createChainProcessR(numberOfProcess - 1);
    }
    else
        wait(NULL);
    
    exit(0);

}

//Problem: Create n number of chain process

int main(int argc, char * argv[])
{
    int numChainProcess = atoi(argv[1]);
    
    // An iterative approach
    //createChainProcess(numChainProcess);

    // A recursive approach
    printf("Process ID: %d Parent ID:%d\n", getpid(), getppid());
    createChainProcessR(numChainProcess);
    return 0;

}