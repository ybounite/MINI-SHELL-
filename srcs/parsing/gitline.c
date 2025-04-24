/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gitline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:41:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/24 20:23:32 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_line()
{
	char *line;

	line = readline(MINISPELL);
	if (!line)
	{
		printf("exit\n");
		rl_clear_history();
		exit(0);
	}
	if (line)
		add_history(line);
	return (line);
}
