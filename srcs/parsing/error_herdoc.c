/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:24:47 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 10:36:37 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_herdoc(char *delimiter)
{
	static int	i;

	i = 1;
	ft_putstr_fd("minishell : here-document at line", 2);
	printf(" %d ", i++);
	printf("delimited by end-of-file (wanted `%s')\n", delimiter);
}

bool	ft_clculate_heredoc(t_env_lst	*list)
{
	int	size;

	size = 0;
	while (list)
	{
		if (list->type == HERE_DOCUMENT)
			size++;
		else if (list->type == PIPE)
			size = 0;
		list = list->next;
	}
	if (size > 16)
		return (ft_putendl_fd("maximum here-document count exceeded", 2),
			ft_malloc(0, 0), exit(2), false);
	return (true);
}
