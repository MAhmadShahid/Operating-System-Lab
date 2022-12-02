#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

	

int main()
{

	// Declared Variables
	char localParentString[30] = { "Hello" };
	char childString[20];
	//char secondString[10];
	int pipeOnefds[2];
	int pipeTwofds[2];
	int returnStatusPipeOne;
	int returnStatusPipeTwo;
	
	returnStatusPipeOne = pipe(pipeOnefds);
	returnStatusPipeTwo = pipe(pipeTwofds);
	
	if ( returnStatusPipeOne == -1 || returnStatusPipeTwo == -1 )
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
		close(pipeOnefds[0]); // use this pipe to write
		close(pipeTwofds[1]); // use this pipe to read
		
		char parentString[20];
		char localChildString[20] = " World";
		
		write(pipeOnefds[1], localChildString, sizeof(localChildString));
		read(pipeTwofds[0], parentString, sizeof(parentString));
		write(1, parentString, sizeof(parentString));
	
		exit(0);
	}
	else
	{
		// wait(NULL);	
		close(pipeOnefds[1]); // use this pipe to read
		close(pipeTwofds[0]); // use this pipe to write
		
		write(pipeTwofds[1], localParentString, sizeof(localParentString));
		read(pipeOnefds[0], childString, sizeof(childString));
	
		write(1, childString , sizeof(childString));
		wait(NULL);
		
	}
	
	return 0;
}