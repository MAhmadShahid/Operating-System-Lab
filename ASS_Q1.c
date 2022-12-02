#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int args, char * argv[])
{
    printf("Executing\n");
    //pipe creation
    int pipefds[2];
    int returnStatus = pipe(pipefds);

    if ( returnStatus == -1 )
    {
        printf("Pipe Creation Failed!");
        return(1);
    }

    printf("Pipe Creation Successful\n");

    
    pid_t pid = fork();

    if ( pid != 0 )
    {
        close(pipefds[0]);
        write(pipefds[1], argv[1], sizeof(argv[1]));
        printf("%s", argv[1]);
    }
    
    if ( pid == 0 )
    {
        close(pipefds[1]);
        char localFileName[35];
        read(pipefds[0], localFileName, sizeof(localFileName));
        printf("\n%s", localFileName);

        FILE * filePointer = fopen(localFileName, "r");
        char currentCharacter;
        int numberOfCharacters = 0;
        int numberOfWords = 0;

        if ( filePointer == NULL )
        {
            printf("Couldn't open file");
            exit(0);
        }

        currentCharacter = fgetc(filePointer);

        while( currentCharacter != EOF )
        {
            if ( currentCharacter == ' ' && currentCharacter == '\n')
                numberOfWords++;
            else
                numberOfCharacters++;

            currentCharacter = fgetc(filePointer);
        }

        numberOfWords++;

        printf("Stats For File: %s\n", localFileName);
        printf("Number Of Words : %d", numberOfWords);
        printf("Number Of Chars : %d", numberOfCharacters);
    
        exit(0);
    }
    else
        wait(NULL);


}