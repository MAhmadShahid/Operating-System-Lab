#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    //declared variables
    pid_t pid;
    FILE *filePointer;
    char currentCharacter;
    int fds[2];
    int returnStatus;

    //initialized variables
    int noOfCharacters = 0;
    int noOfWords = 0;

    //pipe creation
    returnStatus = pipe(fds);

    if (returnStatus == -1)                                   // in case pipe creation was not successful
    {
        printf("\nError In Pipe Creation\n");
        return 1;
    }

    pid = fork();                                            // creation of ith fan process

    if ( pid != 0 )                                         // if the current process is parent process
    {
        // write file's name onto the pipe
        close(fds[0]);
        char fileName[30] = "favouriteRestaurants.txt";
        write(fds[1], fileName, sizeof(fileName));
    }


    if ( pid == 0 )                                         // if current process is a child process
    {
        close(fds[1]);
        char fileName[30];
        read(fds[0], fileName, sizeof(fileName));

        filePointer = fopen(fileName, "r");

        if (filePointer == NULL)
        {
            printf("\nFile Couldn't Open\n");
            return(1);
        }
        printf("Content of this file is:\n");
        
        currentCharacter = fgetc(filePointer);

        while ( currentCharacter != EOF )
        {
            
            noOfCharacters++;

            if ( currentCharacter == ' ' || currentCharacter == '\n' || currentCharacter == '\0' || currentCharacter == '\t' ) 
                noOfWords++;

            currentCharacter = fgetc(filePointer);

        } 

        fclose(filePointer);                                // close file's pointer

        //print the stats for characters and words
        printf("\nNo of characters = %d\n", noOfCharacters);
        printf("No of words = %d\n", noOfWords+1);

        
        exit(0);
    }
    else
    {
        // making the parent wait until child completes its task
        wait(NULL);
    }

    return 0;
}