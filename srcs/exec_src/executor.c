#include "../../includes/minishell.h"
#include "../libraries/libft/libft.h"

// static char	*find_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*path_env;
// 	char	*full_path;
// 	int		i;

// 	(void)envp;
// 	path_env = getenv("PATH");
// 	if (!path_env)
// 		return (NULL);
// 	paths = ft_split(path_env, ':');
// 	if (!paths)
// 		return (NULL);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		full_path = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin_free(full_path, cmd);
// 		if (access(full_path, X_OK) == 0)
// 			return (full_path);
// 		free(full_path);
// 		i++;
// 	}
// 	ft_free_split(paths);
// 	return (NULL);
// }
int	lstsize(t_env_lst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	**git_array(t_env_lst **list)
{
	char	**args;
	int		i;
	int		size;

	if (!list)
		return (NULL);
	size = lstsize(*list); // Ensure lstsize works correctly
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*list && (*list)->type == CMD)
	{
		args[i++] = ft_strdup((*list)->value); // Duplicate the value
		*list = (*list)->next;
	}
	args[i] = NULL; // Null-terminate the array
	return (args);
}
void	execute_command(t_string *st_string)
{
	// char	**args;
	// // pid_t	pid;
	// // char	*cmd_path;
	// int i;
	// i = 0;

	// args = git_array(st_string->head);
	// while(args[i])
	// {
	// 	printf("%s\n", args[i]);
	// 	i++;
	// }
	execute_pipeline(st_string);
	// ft_free_split(args);
}
