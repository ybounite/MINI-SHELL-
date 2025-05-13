/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:27:14 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 06:55:10 by bamezoua         ###   ########.fr       */
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
	t_env_lst	*prev;
	char		**words;
	int			i;

	start = *node_ptr;
	next = start->next;
	words = ft_split(variable, ' ');
	if (!words || !words[0])
		return ;
	i = 0;
	start->value = words[i++];
	start->type = CMD;
	prev = start;
	while (words[i])
	{
		prev->next = ft_newnode(words[i++], CMD);
		prev = prev->next;
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
