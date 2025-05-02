/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:07:38 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/02 10:03:06 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	memory_released(t_list **head)
{
	ft_lstclear(head, free);
}

void	*ft_malloc(size_t size, short option)
{
	static t_list	*head;
	t_list			*new;
	void			*ptr;

	if (option == 1)
	{
		ptr = malloc(size);
		if (!ptr)
			return (memory_released(&head), exit(EXIT_FAILURE), NULL);
		new = ft_lstnew(ptr);
		if (!new)
			return (memory_released(&head), exit(EXIT_FAILURE), NULL);
		ft_lstadd_back(&head, new);
		return (ptr);
	}
	if (option == 0)
		memory_released(&head);
	return (NULL);
}
