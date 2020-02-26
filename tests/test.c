#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

typedef struct stat t_stat;

int main(void)
{
/*
**	access
*/

	printf("access : %d\n", access("a.out", W_OK));
/*
**	fork
*/

	pid_t a;
	a = fork();
	printf("errono : %d\n", errno);

/*
**	getcwd
**	needs to be freed later
*/

	char *buf;

	buf = NULL;
	buf = getcwd(buf, 1);
	printf("getcwd : %s\n", buf);
	free(buf);
	buf = NULL;
	buf = (char*)malloc(sizeof(char) * 50);
	getcwd(buf, 50);
	printf("getcwd : %s\n", buf);
	free(buf);

/*
**	fstat 
*/
	
	t_stat sb;
	int fd;

	fd = open("test.c", O_RDONLY);
	fstat(fd, &sb);
	printf("sb.st_mode : %d\n", sb.st_mode);


	return (0);
}