/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:12 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/09 16:16:17 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_variable_name(const char *str, int *i)
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

char	*get_variable_value(char *var_name)
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
	value = get_env_value(var_name, data_struc());
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_string(const char *str, bool *is_spliting)
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
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			result = ft_strjoin(result, "$$");
			i += 2;
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
			if (!in_double_quotes && !in_single_quotes)
				*is_spliting = 1;
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
void ft_add_expand_variable(t_env_lst **node_ptr, char *variable)
{
	t_env_lst	*start = *node_ptr;
	t_env_lst	*next = start->next; // Save the original next

	char		**words = ft_split(variable, ' ');
	int			i = 0;
	if (!words || !words[0])
		return ;
	start->value = words[i++];
	start->type = CMD; // or whatever makes sense
	t_env_lst *prev = start;
	// Add remaining words as new nodes
	while (words[i])
	{
		t_env_lst *new_node = ft_newnode(words[i++], CMD);
		prev->next = new_node;
		prev = new_node;
	}
	prev->next = next;
	*node_ptr = prev;
}

bool	is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	expand_variables(t_env_lst *list)
{
	t_env_lst	*current;
	char		*expanded;
	bool		is_spliting;

	is_spliting = 0;
	current = list;
	while (current)
	{
		if (current->value && ft_strchr(current->value, '$'))
		{
			expanded = expand_string(current->value, &is_spliting);
			printf("%sexpand : %s\e[0m\n", YELLOW, expanded);
			if (is_spliting && !is_equal(expanded))
			{
				
				ft_add_expand_variable(&current, expanded);
				is_spliting = 0;
			}
			else
				current->value = expanded;
		}
		current = current->next;
	}
}
