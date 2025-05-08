/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_allocation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:27:46 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/08 09:26:27 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_destroylist(t_env_lst *list)
{
	t_env_lst	*tmp;

	tmp = list;
	if (!list)
		return ;
	while (tmp)
	{
		list = list->next;
		free(tmp);
		tmp = list;
	}
}
