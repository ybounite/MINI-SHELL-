#include "../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(255); // Always exit with code 255 for non-numeric arguments
		}
		else if (args[2])
		{
			printf("exit: too many arguments\n");
			g_last_exit_status = 1;
			return ; // Don't exit if too many arguments
		}
		else
		{
			exit_code = ft_atoi(args[1]);
		}
	}
	exit(exit_code);
}

void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		// Only display variables with values (containing '=')
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
}
