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

char	*get_env_value(char *var_name, t_string *st_string)
{
	int		i;
	int		len;

	if (!var_name || !st_string || !st_string->g_envp)
		return (ft_strdup(""));
	
	if (var_name[0] == '$')
		var_name++;
	len = ft_strlen(var_name);
	if (len == 0)
		return (ft_strdup(""));
		
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], var_name, len) == 0
			&& st_string->g_envp[i][len] == '=')
		{
			return (ft_strdup(st_string->g_envp[i] + len + 1));
		}
		i++;
	}
	
	return (ft_strdup(""));
}

void	builtin_echo(char **args, t_string *st_string)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	(void)st_string;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		// if (args[i + 1])
		// 	printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
