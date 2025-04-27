/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:45:11 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/27 17:04:47 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_lst	*ft_newnode(char *cmd, en_status state)
{
	t_env_lst *new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->value = cmd;
	new->type = state;
	new->cat = 0;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_env_lst **head, t_env_lst *new)
{
	t_env_lst	*ptr;

	if (!new)
		return ;
	if (!*head || !head)
	{
		*head = new;
		return ;
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

void	ft_add_newtoken(t_env_lst **head, char *token, en_status state)
{
	t_env_lst	*new;
	new = ft_newnode(token, state);
	if (!new)
		return ;
	lstadd_back(head, new);
}
