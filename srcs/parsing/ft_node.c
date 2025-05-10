/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:45:11 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 09:22:50 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_lst	*ft_newnode(char *cmd, en_status state)
{
	t_env_lst *new;

	new = ft_malloc(sizeof(t_env_lst), true);
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

char *string(en_status type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == APPEND_REDIRECTION)
		return ("APPEND_REDIRECTION");
	else if (type == HERE_DOCUMENT)
		return ("HERE_DOCUMENT");
	else if (type == INPUT_REDIRECTION)
		return ("INPUT_REDIRECTION");
	else if (type == OUTPUT_REDIRECTION)
		return ("OUTPUT_REDIRECTION");
	else if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == BUILTINS)
		return ("BUILTINS");
	else
		return ("CMD");
}

void print_lst_tokens(t_env_lst *head)
{
	int	i = 0;
	while (head)
	{
		printf("[Token %d]: %s%s\e[0m, Type: \e[1;37m%s%s \e[0m\n", i++, GREEN,head->value, GREEN,string(head->type));
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
