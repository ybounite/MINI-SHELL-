/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:18:12 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 14:25:55 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lenoperator(char *str, int *index)
{
	int		i;
	char	operator;

	i = 0;
	operator = str[*index];
	while (str[*index] && str[*index] == operator)
	{
		(*index)++;
		i++;
	}
	return (i);
}

void	handle_operator(char *line, int *i, char **spliter, int *index)
{
	int		start;
	char	*str;

	start = *i;
	str = ft_malloc(sizeof(char) * ft_lenoperator(line, i) + 1, 1);
	ft_strncpy(str, line + start, *i - start);
	str[*i - start] = '\0';
	spliter[(*index)++] = str;
}

void	handle_word(char *line, int *i, char **spliter, int *index)
{
	int		start;
	char	*str;

	start = *i;
	skip_whiteword(line, i);
	str = ft_malloc(*i - start + 1, 1);
	ft_strncpy(str, line + start, *i - start);
	str[*i - start] = '\0';
	spliter[(*index)++] = str;
}

char	**spliter(char *line)
{
	int		i;
	char	**spliter;
	int		index;

	(1) && (i = 0), (index = 0);
	spliter = (char **)ft_malloc(sizeof(char *) * (lentcommand(line) + 1), 1);
	while (line[i])
	{
		ft_skip_whitespace(line, &i);
		if (line[i] == '\0')
			break ;
		if (is_operator(line[i]))
			handle_operator(line, &i, spliter, &index);
		else
			handle_word(line, &i, spliter, &index);
	}
	spliter[index] = NULL;
	data_struc()->size = index;
	return (spliter);
}
