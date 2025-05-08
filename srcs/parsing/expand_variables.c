/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:12 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/08 09:12:30 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_variable_name(const char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i + 1; // Skip '$'
	len = 0;
	if (!str[start])
		return (NULL);
	if (str[start] == '?')
	{
		*i += 2;
		return (ft_strdup("?"));
	}
	while (str[start + len] && (ft_isalnum(str[start + len]) || str[start
			+ len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	*i += len + 1;
	return (var_name);
}

static char	*get_variable_value(char *var_name)
{
	char	*value;
	char	*exit_status_str;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_status_str = ft_itoa(data_struc()->exit_status);
		return (exit_status_str);
	}
	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

 char	*expand_string(const char *str)
{
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		original_i;

	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	result = ft_strdup("");
	//$1PWD
	while (str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i+1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			result = ft_strjoin(result, "$$");
			i +=2;
		}
		else if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
		else if (str[i] == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
		else if (str[i] == '$' && !in_single_quotes)
		{
			original_i = i;
			var_name = get_variable_name(str, &i);
			var_value = get_variable_value(var_name);
			temp = result;
			result = ft_strjoin(result, var_value);
			if (original_i == i)
			{
				temp = result;
				result = ft_strjoin_char(result, '$');
				i++;
			}
		}
		else
		{
			temp = result;
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = (char *)ft_malloc(sizeof(char) * (len + 2), 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}

void	expand_variables(t_env_lst *list)
{
	t_env_lst	*current;
	char		*expanded;

	current = list;
	while (current)
	{
		if (current->value && ft_strchr(current->value, '$'))
		{
			expanded = expand_string(current->value);
			printf("---------------->Expanded: %s\n", expanded);
			current->value = expanded;
		}
		current = current->next;
	}
}
