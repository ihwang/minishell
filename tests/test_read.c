#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char buf[100];
	int	ret;

	ret = read(0, buf, 100);
	printf("read %s\n", buf);

	return (0);
}
