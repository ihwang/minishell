#include <stdio.h>
int main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("FOOOOOO! %s\n", av[1]);
	}
	else
		printf("FOOOOOO!\n");
	return (0);
}
