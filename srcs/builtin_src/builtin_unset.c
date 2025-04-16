#include "../../includes/minishell.h"

static int	is_valid_unset_key(char *key)
{
	int	i;

	i = 0;
	if (!key || !key[0] || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_env_var(char *key, char ***envp)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	if (!key || !is_valid_unset_key(key))
		return ;
	len = ft_strlen(key);
	i = 0;
	// Count the number of environment variables that don't match the key
	for (i = 0; (*envp)[i]; i++)
		if (!(!ft_strncmp((*envp)[i], key, len) && (*envp)[i][len] == '='))
			i++;
	// Allocate new environment array with one less entry
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	// Copy all variables except the one to be unset
	while ((*envp)[i])
	{
		if (!(!ft_strncmp((*envp)[i], key, len) && (*envp)[i][len] == '='))
			new_env[j++] = (*envp)[i];
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
}

void	builtin_unset(char **args, char ***envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_unset_key(args[i]))
			unset_env_var(args[i], envp);
		else
			printf("unset: `%s': not a valid identifier\n", args[i]);
		i++;
	}
}
