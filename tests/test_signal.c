#include <signal.h>
#include <stdio.h>

void	handle_sigint(int sig)
{
	printf("Caught signal %d\n", sig);
}

int main(void)
{
	signal(SIGINT, handle_sigint);
	while (1);
	return (0);
}
