/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:46:47 by bamezoua          #+#    #+#             */
/*   Updated: 2024/11/05 10:00:09 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*next;

	if (!lst || !del || !*lst)
		return ;
	p = *lst;
	while (p != NULL)
	{
		next = p->next;
		del(p->content);
		free(p);
		p = next;
	}
	*lst = NULL;
}
