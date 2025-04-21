#include "../../includes/minishell.h"

void	builtin_env(t_string *st_string)
{
    int	i;

    i = 0;
    while (st_string->g_envp[i])
    {
        printf("%s\n", st_string->g_envp[i]);
        i++;
    }
}
