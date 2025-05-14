/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_expand_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:09:39 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/14 13:10:22 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	ft_create_nodes_from_words(t_env_lst *start, char **words, int i,
		t_env_lst *next)
{
	t_env_lst	*prev;
	t_env_lst	*new_node;

	prev = start;
	while (words[i])
	{
		new_node = ft_newnode(words[i++], CMD);
		prev->next = new_node;
		prev = new_node;
	}
	prev->next = next;
}

void	ft_add_expand_variable(t_env_lst **node_ptr, char *variable)
{
	t_env_lst	*start;
	t_env_lst	*next;
	char		**words;
	int			i;

	start = *node_ptr;
	next = start->next;
	i = 0;
	words = ft_split(variable, ' ');
	if (!words || !words[0])
		return ;
	start->value = words[i++];
	start->type = CMD;
	ft_create_nodes_from_words(start, words, i, next);
	*node_ptr = start;
}
