#include "../includes/minishell.h"

// Only one global variable
int			g_last_exit_status = 0;

static char	**duplicate_envp(char **envp)
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
	char	*line;
	char	**env_copy;
	int		should_exit;

	should_exit = 0;
	(void)argc;
	(void)argv;
	env_copy = duplicate_envp(envp);
	if (!env_copy)
	{
		perror("Failed to initialize environment");
		return (1);
	}
	setup_signals();
	while (!should_exit)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			execute_command(line, env_copy);
		}
		free(line);
	}
	ft_free_split(env_copy); // Free the duplicated environment
	return (g_last_exit_status);
}
