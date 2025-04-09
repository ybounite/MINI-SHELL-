/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:49:01 by ybounite          #+#    #+#             */
/*   Updated: 2025/01/27 16:08:45 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	ptr = *lst;
	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		*lst = (*lst)->next;
		del(ptr->content);
		free(ptr);
		ptr = *lst;
	}
}
