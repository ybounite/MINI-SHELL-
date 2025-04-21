#include "../../includes/minishell.h"

static int	env_len(t_string *st_string)
{
	int	i;

	i = 0;
	while (st_string->g_envp[i])
		i++;
	return (i);
}

static void	sort_env(char **env)
{
	char	*tmp;

	int i, j;
	size_t len_i, len_j;
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			len_i = ft_strlen(env[i]);
			len_j = ft_strlen(env[j]);
			if (len_i > len_j)
			{
				if (ft_strncmp(env[i], env[j], len_j) > 0)
				{
					tmp = env[i];
					env[i] = env[j];
					env[j] = tmp;
				}
			}
			else
			{
				if (ft_strncmp(env[i], env[j], len_i) > 0)
				{
					tmp = env[i];
					env[i] = env[j];
					env[j] = tmp;
				}
			}
			j++;
		}
		i++;
	}
}

static char	**create_env_copy(t_string *st_string)
{
	char	**copy;

	int i, size;
	size = env_len(st_string);
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(st_string->g_envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	print_env_entry(char *entry)
{
	char	*sep;

	sep = ft_strchr(entry, '=');
	if (sep)
		printf("declare -x %.*s=\"%s\"\n", (int)(sep - entry), entry, sep + 1);
	else
		printf("declare -x %s\n", entry);
}

static void	print_export(t_string *st_string)
{
	char	**copy;
	int		i;

	copy = create_env_copy(st_string);
	if (!copy)
		return ;
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		print_env_entry(copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
}

static char	*extract_key(char *arg, int *key_len)
{
	*key_len = 0;
	while (arg[*key_len] && arg[*key_len] != '=')
		(*key_len)++;
	return (ft_substr(arg, 0, *key_len));
}

static char	*create_entry(char *arg, int key_len)
{
	char	*value;
	int		value_len;
	char	*key_part;
	char	*value_part;
	char	*result;

	if (arg[key_len] == '\0')
		return (ft_strjoin(arg, "="));
	else if (arg[key_len] == '=')
	{
		// Handle the value part possibly containing quotes
		value = arg + key_len + 1;
		value_len = ft_strlen(value);
		// If value is quoted, remove the quotes
		if (value_len >= 2 && value[0] == '"' && value[value_len - 1] == '"')
		{
			// Create a new string: key= + value_without_quotes
			key_part = ft_substr(arg, 0, key_len + 1);
			value_part = ft_substr(value, 1, value_len - 2);
			result = ft_strjoin(key_part, value_part);
			free(key_part);
			free(value_part);
			return (result);
		}
	}
	return (ft_strdup(arg));
}

static int	update_existing_entry(char *key, int key_len, char *entry,
		t_string *st_string)
{
	int	i;

	i = 0;
	while (st_string->g_envp[i])
	{
		if (!ft_strncmp(st_string->g_envp[i], key, key_len)
			&& st_string->g_envp[i][key_len] == '=')
		{
			free(st_string->g_envp[i]);
			st_string->g_envp[i] = entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_new_entry(char *entry, t_string *st_string)
{
	int		len;
	char	**new_env;
	int		i;

	len = env_len(st_string);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
	{
		free(entry);
		return ;
	}
	i = 0;
	while (i < len)
	{
		new_env[i] = st_string->g_envp[i];
		i++;
	}
	new_env[len] = entry;
	new_env[len + 1] = NULL;
	free(st_string->g_envp);
	st_string->g_envp = new_env;
}

static void	add_or_update(char *arg, t_string *st_string)
{
	int		key_len;
	char	*key;
	char	*entry;

	key = extract_key(arg, &key_len);
	if (!key)
		return ;
	if (!is_valid_key(key))
	{
		printf("export: `%s`: not a valid identifier\n", arg);
		free(key);
		return ;
	}
	entry = create_entry(arg, key_len);
	if (!entry)
	{
		free(key);
		return ;
	}
	if (!update_existing_entry(key, key_len, entry, st_string))
		add_new_entry(entry, st_string);
	free(key);
}

void	builtin_export(char **args, t_string *st_string)
{
	int i;

	if (!args[1])
	{
		print_export(st_string);
		return ;
	}
	i = 1;
	while (args[i])
	{
		add_or_update(args[i], st_string);
		i++;
	}
}