#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

	

int main(int argc, char * argv[])
{
	
	pid_t pid;
	
	int n = pipe(pid);
	int c = pid = fork();
	
	if ( n == -1 || c == -1 )
	{
		perror("Failiuuuuuuuuure");
	}
	
	if ( pid == 0 )
	{
		if ( dup2(fd[1], STDOUT.FILENO) == -1 )
			perror("Failed Redirection");
		else if ( (close(fd[0]) == -1 || (close(fd[1]) == -1 )
			perror("Failed to close pipe");
		else
		{
			execl("/bin/ls", "ls", "-a", NULL);
			perror("Failed Miserably");
		}
		
		exit(3);
	}
	
	
	return 1;
}