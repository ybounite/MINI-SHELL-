/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gitline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:41:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/08 12:58:42 by bamezoua         ###   ########.fr       */
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
		ft_malloc(0, 0);
		exit(data_struc()->exit_status);
	}
	if (line)
		add_history(line);
	return (line);
}
