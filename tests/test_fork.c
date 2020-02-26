#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int     main(void)
{
    int i;
    pid_t pid;
    int nums[5] = {0, 1, 2, 3, 4};

    pid = fork();

    if (pid == 0)
    {
        i = -1;
        while (++i < 5)
        {
            nums[i] *= -i;
            printf("CHILD: %d\n", nums[i]);
        }
    }
    else if (pid > 0)
    {
        //wait(NULL);
        i = -1;
        while (++i < 5)
        {
            printf("PARENT: %d\n", nums[i]);
        }
    }
    return (0);
}