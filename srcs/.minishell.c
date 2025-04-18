#include "../../includes/minishell.h"

// char **g_envp; // define global

static char **duplicate_envp(char **envp)
{
    int		i;
    int		len;
    char	**new_envp;

    len = 0;
    while (envp[len])
        len++;
    new_envp = malloc(sizeof(char *) * (len + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i])
        {
            while (i > 0)
                free(new_envp[--i]);
            free(new_envp);
            return (NULL);
        }
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

int	main(int argc, char **argv, char **envp)
{
    t_string st_string;

    (void)argc;
    (void)argv;
    st_string.g_envp = duplicate_envp(envp);
    if (!st_string.g_envp)
    {
        perror("Failed to initialize environment");
        return (1);
    }
    setup_signals();
    while (1)
    {
        st_string.line = readline(MINISPELL);
        if (!st_string.line)
        {
            printf("exit\n");
            break ;
        }
        if (*st_string.line)
        {
            add_history(st_string.line);
            execute_command(&st_string);
        }
        free(st_string.line);
    }
    ft_free_split(st_string.g_envp); // Free the duplicated environment
    return (0);
}
