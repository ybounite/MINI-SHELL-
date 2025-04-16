#include "../includes/minishell.h"

char	*find_path(char *cmd, char **envp)
{
    char	**paths;
    char	*path_env;
    char	*full_path;
    int		i;

    (void)envp;
    if (access(cmd, X_OK) == 0) // Check if the command is an absolute path or relative path
        return (ft_strdup(cmd));
    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin_free(full_path, cmd);
        if (access(full_path, X_OK) == 0)
        {
            ft_free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    ft_free_split(paths);
    return (NULL);
}