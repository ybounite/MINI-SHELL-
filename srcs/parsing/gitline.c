/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gitline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:41:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/30 16:59:31 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_line(void)
{
	char	*line;

	line = readline(MINISPELL);
	if (!line)
	{
		printf("exit\n");
		rl_clear_history();
		ft_malloc(0, 0);
		exit(0);
	}
	if (line)
		add_history(line);
	return (line);
}
