#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
//	pid_t	pid;

///	pid = fork();
//	if (pid == 0)
//	{
	char **buf = (char**)malloc(sizeof(char*));

	buf[0] = (char*)malloc(10);
	buf[0] = strcpy(buf[0], "intaek");

		execve("foo", NULL, NULL);
		printf("Child is executed\n");
//	}
//	else if (pid > 0)
//	{
//		wait(NULL);
//		printf("Parent had waited for child\n");
//	}

	return (0);
}
