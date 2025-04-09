/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:26:58 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/07 18:02:24 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **list_path)
{
	int i = 0;
	while (list_path[i])
	{
		free(list_path[i]);
		i++;
	}
	free(list_path);
}

void	free_list(t_env_lst *head)
{
	t_env_lst *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}
