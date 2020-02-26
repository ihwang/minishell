#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    extern char **environ;
	char **en_cp;
    int i;

	en_cp = environ;
    i = -1;
    while (en_cp[++i])
    {
        if (strstr(en_cp[i], "PATH"))
            printf("%s\n", en_cp[i]);
    }
    
    return (0);
}
