/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_allocation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:27:46 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/06 14:27:49 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_destroylist(t_env_lst *list)
{
	t_env_lst *tmp;
	tmp = list;
	while (tmp)
	{
		list = list->next;
		free(tmp);
		tmp = list;
	}
}
