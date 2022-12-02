#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int args, char * argv[])
{
    //pipe creation
    int pipefds[2];
    int returnStatus = pipe(pipefds);

    if ( returnStatus == -1 )
    {
        printf("Pipe Creation Failed!");
        return(1);
    }

    //variables
    int numberOfProcess = atoi(argv[1]);
    int sum = 0;
    pid_t pid;

    //write loop
    for( int counter = 0; counter < numberOfProcess; counter ++)
    {
        pid = fork();

        if( pid == 0 )
        {
            close(pipefds[0]); // write on this pipe
            
            char inputNumberChar[20]; 
            
            read(0, inputNumberChar, sizeof(inputNumberChar));
            write(pipefds[1], inputNumberChar, sizeof(inputNumberChar));
            exit(0);
        }
        else
            wait(NULL);
    }

    //read loop
    close(pipefds[1]);
    char printNumber[20];
    char recieveNumber[20];    
    
    for(int counter = 0; counter < numberOfProcess; counter ++)
    {

        read(pipefds[0], recieveNumber, sizeof(recieveNumber));
        sum += atoi(recieveNumber);

        sprintf(printNumber, "\nSum: %d", sum);
    }

    printf("%s", printNumber);

    return 0;
 
}