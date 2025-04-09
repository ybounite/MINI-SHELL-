/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lestnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:37:06 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/07 18:02:24 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*creatnew_node(char *cmd, en_status_type state, bool cat)
{
	t_env_lst *new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->value = cmd;
	new->type = state;
	new->cat = cat;
	new->next = NULL;
	return (new);
}

void lstadd_back(t_env_lst **head, t_env_lst *new)
{
	t_env_lst	*ptr;

	if (!new)
		return;
	if (!*head)
	{
		*head = new;
		return;
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void print_lst_tokens(t_env_lst *head)
{
	int i = 0;
	while (head)
	{
		printf("[Token %d: %s, Type: %d, Cat: %d]\n", i++,head->value, head->type, head->cat);
		head = head->next;
	}
}
