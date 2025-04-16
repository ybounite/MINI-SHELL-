#include "../../includes/minishell.h"

/* Check if a command is a shell builtin */
int	is_builtin(char *command)
{
	char	**args;
	int		result;
	char	*builtins[] = {"cd", "export", "unset", "exit", "echo", "pwd",
			"env", NULL};
	int		i;

	args = ft_split(command, ' ');
	if (!args || !args[0])
		return (0);
	result = 0;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(args[0], builtins[i]) == 0)
		{
			result = 1;
			break ;
		}
		i++;
	}
	ft_free_split(args);
	return (result);
}

/* Execute a builtin command */
int	handle_builtin(char *command, char **envp)
{
	char	**args;
	int		should_exit;

	should_exit = 0;
	args = ft_split(command, ' ');
	if (!args)
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, &envp);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, &envp);
	else if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args, &envp);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(envp);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		should_exit = (args[1] == NULL || is_numeric(args[1]))
			&& (args[2] == NULL);
		builtin_exit(args);
		ft_free_split(args);
		return (should_exit); // Only return 1 if we should actually exit
	}
	g_last_exit_status = 0;
	ft_free_split(args);
	return (should_exit);
}

/* Check if a key is valid for export/unset */
int	is_valid_key(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	// First character must be a letter or underscore
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	// Find equals sign if it exists
	i = 0;
	while (s[i] && s[i] != '=')
	{
		// All characters before equals must be alphanumeric or underscore
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
