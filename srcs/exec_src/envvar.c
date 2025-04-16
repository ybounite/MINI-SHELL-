#include "../includes/minishell.h"

/* Process $? exit status variable */
static char	*process_exit_status(char *result, int *i)
{
	char	*exit_str;
	char	*tmp;

	(*i)++; // Skip the '?'
	tmp = result;
	exit_str = ft_itoa(g_last_exit_status);
	if (!exit_str)
	{
		free(result);
		return (NULL);
	}
	result = ft_strjoin(result, exit_str);
	free(tmp);
	free(exit_str);
	return (result);
}

/* Extract environment variable name */
char	*get_env_var_name(const char *str, int *i)
{
	int	start;
	int	len;

	start = *i + 1; // Skip the '$'
	len = 0;
	while (str[start + len] && (ft_isalnum(str[start + len]) || str[start
			+ len] == '_'))
		len++;
	*i = start + len - 1;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_substr(str, start, len));
}

/* Find environment variable value */
char *get_env_value(const char *name, char **envp)
{
    int    i;
    int    len;

    if (!name || !*name)
        return (ft_strdup(""));
    len = ft_strlen(name);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (ft_strdup(&envp[i][len + 1]));
        i++;
    }
    return (ft_strdup(""));
}

/* Process environment variable */
char	*process_env_var(char *result, const char *str, int *i, char **envp)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	if (str[*i + 1] == '?')
		return (process_exit_status(result, i));
	var_name = get_env_var_name(str, i);
	if (!var_name)
	{
		free(result);
		return (NULL);
	}
	var_value = get_env_value(var_name, envp);
	free(var_name);
	if (!var_value)
	{
		free(result);
		return (NULL);
	}
	tmp = result;
	result = ft_strjoin(result, var_value);
	free(tmp);
	free(var_value);
	return (result);
}

/* Main function to expand environment variables */
char	*expand_env_variables(char *str, char **envp)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '_' || str[i + 1] == '?'))
		{
			result = process_env_var(result, str, &i, envp);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char(result, str[i]);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}
