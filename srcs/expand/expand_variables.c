/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:12 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/14 10:25:15 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ft_add_expand_variable(t_env_lst **node_ptr, char *variable)
{
	t_env_lst	*start;
	t_env_lst	*next;
	int			i;
	t_env_lst	*prev;
	char		**words;
	t_env_lst	*new_node;

	start = *node_ptr;
	next = start->next;
	i = 0;
	words = ft_split(variable, ' ');
	if (!words || !words[0])
		return ;
	start->value = words[i++];
	start->type = CMD;
	prev = start;
	while (words[i])
	{
		new_node = ft_newnode(words[i++], CMD);
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

bool	ft_isambiguous(t_env_lst *prev, char *str)
{
	return ((prev && (prev->type == INPUT_REDIRECTION
				|| prev->type == OUTPUT_REDIRECTION
				|| prev->type == APPEND_REDIRECTION)) && (str == NULL
			|| str[0] == '\0' || ft_strchr(str, ' ')));
}

int	expand_variables(t_env_lst **list)
{
	t_env_lst	*current;
	t_env_lst	*prev;
	char		*expanded;
	bool		is_spliting;

	is_spliting = 0;
	current = *list;
	prev = NULL;
	while (current)
	{
		if (current->value && ft_strchr(current->value, '$'))
		{
			expanded = expand_string(current->value, &is_spliting);
			if (ft_isambiguous(prev, expanded))
			{
				printf("minishell: %s: ambiguous redirect\n", current->value);
				return (-1);
			}
			current->value = "";
			if (is_spliting && !is_equal(expanded))
			{
				ft_add_expand_variable(&current, expanded);
				is_spliting = 0;
			}
			else
				current->value = expanded;
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
