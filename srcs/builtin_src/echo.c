#include "../../includes/minishell.h"

int	is_n_flag(char *s)
{
    int	i;

    if (!s || s[0] != '-' || s[1] != 'n')
        return (0);
    i = 1;
    while (s[i] == 'n')
        i++;
    return (s[i] == '\0');
}

void	builtin_echo(char **args)
{
    int	i;
    int	n_flag;

    i = 1;
    n_flag = 0;
    while (args[i] && is_n_flag(args[i]))
    {
        n_flag = 1;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!n_flag)
        printf("\n");
}