#include "../includes/minishell.h"

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	builtin_export(char **args, char ***envp)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		print_export(*envp);
		return ;
	}
	while (args[i])
	{
		if (is_valid_key(args[i]))
			add_or_update(args[i], envp);
		else
			printf("export: `%s`: not a valid identifier\n", args[i]);
		i++;
	}
}

// static char	*extract_key(char *arg, int *key_len)
// {
// 	*key_len = 0;
// 	while (arg[*key_len] && arg[*key_len] != '=')
// 		(*key_len)++;
// 	return (ft_substr(arg, 0, *key_len));
// }

void	add_or_update(char *arg, char ***envp)
{
    char	*key;
    int		key_len;
    char	*entry;
    char	*equals_pos;

    // Find the position of the equals sign, if it exists
    equals_pos = ft_strchr(arg, '=');
    
    // Extract the key (variable name)
    if (equals_pos)
        key_len = equals_pos - arg;
    else
        key_len = ft_strlen(arg);
        
    key = ft_substr(arg, 0, key_len);
    if (!key || !is_valid_key(key))
    {
        if (key)
            free(key);
        printf("export: `%s`: not a valid identifier\n", arg);
        return ;
    }
    
    // Create the entry to add to environment
    entry = ft_strdup(arg); // Copy as is, whether it has '=' or not
    if (!entry)
    {
        free(key);
        return ;
    }
    
    // Update or add to environment
    if (!update_existing_env(key, key_len, entry, *envp))
        add_new_env(entry, envp);
        
    free(key);
}
