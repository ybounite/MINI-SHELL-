/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gitline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:41:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/14 09:41:49 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_line(void)
{
	char	*line;

	line = readline(MINISPELL); 
	// line = readline("MINISHELL");
	if (!line)
	{
		printf("exit\n");
		ft_malloc(0, 0);
		exit(g_exit_status);
	}
	if (line)
		add_history(line);
	return (line);
}
