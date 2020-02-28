#include <unistd.h>
#include <stdio.h>
#include "../libft/includes/libft.h"

int main(void)
{
    char *test1 = ft_strnew(10);
    char **split;

    test1 = ft_strcpy(test1, "abcefg");
    split = ft_strsplit(test1, ';');
	return (0);
}
