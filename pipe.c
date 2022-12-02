#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

	

int main()
{

	// Declared Variables
	char firstString[40];
	//char secondString[10];
	int fds[2];
	int returnStatus;
	
	returnStatus = pipe(fds);
	
	if ( returnStatus == -1 )
	{
		printf("Error in file creation");
		return 2;
	}
	
	pid_t pid;
	
	pid = fork();
	
	if ( pid < 0 )
	{
		printf("Process Creation Failed!");
		return 1;
	}
	if ( pid == 0 )
	{
		// Approach Number 1
		//char localFirstString[20] = { "Hello" };
		//char localSecondString[20] = { "Hi" };
		
		//firstString = localFirstString;
		//secondString = localSecondString;
		
		//Approach Number 2
		close(fds[0]);
		char localFirstString[20] = { "Hello" };
		char localSecondString[20] = { "Gamers!" };
		
		write(fds[1], localFirstString, sizeof(localFirstString));
		write(fds[1], localSecondString, sizeof(localSecondString));
		
		exit(0);
	}
	else
	{
		wait(NULL);	
		close(fds[1]);
		
		read(fds[0], firstString, sizeof(firstString));
		
        strcat(firstString, " "); //firstString[strlen(firstString)] = ' ';
		
		read(fds[0], firstString + strlen(firstString), sizeof(firstString));
         // read(fds[0], secondString, sizeof(secondString));
        //	strcat(firstString, secondString);

		write(1, firstString , sizeof(firstString)); 


        char string[10] = "he\0he";
        printf("%s", string);
		//printf("%s", firstString);
	}
	
	return 0;
}