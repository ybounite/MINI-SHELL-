/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:36:53 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/16 14:57:22 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_pipe(t_env_lst *list)
{
	t_env_lst	*current;

	current = list;
	while (current)
	{
		if (current->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

int	lstsize(t_env_lst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	shift_empty_args(char **args)
{
	int	i;

	i = 0;
	if (args && args[0] && args[0][0] == '\0' && args[1] != NULL)
	{
		while (args[i + 1])
		{
			args[i] = args[i + 1];
			i++;
		}
		args[i] = NULL;
	}
}
