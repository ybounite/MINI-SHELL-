#include "../includes/minishell.h"

int	update_existing_env(char *key, int key_len, char *entry, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		// Check if the variable name matches (up to the key_len)
		// and is followed by '=' or is the end of the string
		if (!ft_strncmp(envp[i], key, key_len) && (envp[i][key_len] == '='
				|| envp[i][key_len] == '\0'))
		{
			free(envp[i]);
			envp[i] = entry;
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_new_env(char *entry, char ***envp)
{
	int		len;
	int		i;
	char	**new_env;

	len = env_len(*envp);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
	{
		free(entry);
		return ;
	}
	// Copy existing environment variables
	for (i = 0; i < len; i++)
		new_env[i] = (*envp)[i];
	// Add the new entry
	new_env[i] = entry;
	new_env[i + 1] = NULL;
	// Free the old array but not its contents
	free(*envp);
	*envp = new_env;
}

void	sort_env(char **env)
{
	char	*tmp;
	int		i;
	int		j;
	int		min_len;

	for (i = 0; env[i]; i++)
	{
		for (j = i + 1; env[j]; j++)
		{
			min_len = ft_strlen(env[i]) > ft_strlen(env[j]) ? ft_strlen(env[j]) : ft_strlen(env[i]);
			if (ft_strncmp(env[i], env[j], min_len) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
		}
	}
}

char	**create_sorted_env_copy(char **envp)
{
	int		i;
	int		size;
	char	**copy;

	size = env_len(envp);
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	sort_env(copy);
	return (copy);
}
