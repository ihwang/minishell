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
	char **buf = (char**)malloc(sizeof(char*) * 2);

	buf[0] = (char*)malloc(10);
	buf[0] = strcpy(buf[0], "foo");
//	buf[1] = (char*)malloc(10);
//	buf[1] = strcpy(buf[1], "intaek!");
	buf[1] = NULL;

		execve("foo", buf, NULL);
		printf("Child isn't executed\n");
//	}
//	else if (pid > 0)
//	{
//		wait(NULL);
//		printf("Parent had waited for child\n");
//	}

	return (0);
}
