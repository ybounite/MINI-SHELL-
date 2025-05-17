/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:12 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/17 20:21:27 by bamezoua         ###   ########.fr       */
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

bool	ft_isambiguous(t_env_lst *prev, char *str)
{
	return ((prev && (prev->type == INPUT_REDIRECTION
				|| prev->type == OUTPUT_REDIRECTION
				|| prev->type == APPEND_REDIRECTION)) && (str == NULL
			|| str[0] == '\0' || ft_strchr(str, ' ')));
}

static int	handle_ambiguous_redirect(t_env_lst *prev, char *expanded,
		const char *value)
{
	if (ft_isambiguous(prev, expanded))
		printf("minishell: %s: ambiguous redirect\n", value);
	return (0);
}

static void	process_expanded_value(t_env_lst **current, char *expanded,
		bool *is_spliting)
{
	if (*is_spliting && !is_equal(expanded))
	{
		ft_add_expand_variable(current, expanded);
		*is_spliting = 0;
	}
	else
		(*current)->value = expanded;
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
			if (handle_ambiguous_redirect(prev, expanded, current->value) == -1)
				return (-1);
			current->value = "";
			process_expanded_value(&current, expanded, &is_spliting);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
