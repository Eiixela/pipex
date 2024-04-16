#include <stdio.h>

int	main(int ac, char **av, char **env)
{
    int j = 0;
    int i =0;
    while (ac)
        i++;
    while (av)
        i++;
    while (env)
    {
        printf("%s\n", env[j]);
        j++;
    }
    return 0;

}