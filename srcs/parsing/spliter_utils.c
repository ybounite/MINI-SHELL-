/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:29:55 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 09:39:44 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_count_whitchar(char *line, int *index, int *count, char c)
{
	while (line[*index] && line[*index] == c)
		(*index)++;
	(*count)++;
}

int	lentcommand(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		ft_skip_whitespace(line, &i);
		if (line[i] == '\0')
			break ;
		if (line[i] == PIPE)
			ft_count_whitchar(line, &i, &count, '|');
		else if (line[i] == '<')
			ft_count_whitchar(line, &i, &count, '<');
		else if (line[i] == '>')
			ft_count_whitchar(line, &i, &count, '>');
		else
		{
			skip_whiteword(line, &i);
			count++;
		}
	}
	return (count);
}
