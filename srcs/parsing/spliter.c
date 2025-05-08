/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:18:12 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/08 08:37:10 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void skip_whiteword(char *str, int *i)
{
	char qouts;
	
	while (str[*i] && !find_space(str[*i]) && !is_operator(str[*i]))
	{
		if (isquotes(str[*i]))
		{
			qouts = str[(*i)++];
			while (str[*i] && str[*i] != qouts)
				(*i)++;
			if (isquotes(str[*i]))
				(*i)++;
		}
		else
			(*i)++;
	}
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
			break;
		if (is_operator(line[i]))
		{
			while(line[i] && is_operator(line[i]))
				i++;
			count++;
		}
		else
		{
			skip_whiteword(line, &i);
			count++;
		}
	}
	return (count);
}

int	ft_lenoperator(char *str, int *index)
{
	int i;

	i = 0;
	while (str[*index] && is_operator(str[*index]))
	{
		(*index)++;
		i++;
	}
	return (i);
}

char	**spliter(char *line)
{
	int		i = 0;
	char	**spliter;
	char	*str = NULL;
	int		index = 0;
	spliter = (char **)ft_malloc(sizeof(char *) * (lentcommand(line) + 1), 1);
	while (line[i])
	{
		ft_skip_whitespace(line, &i);
		if (line[i] == '\0')
			break;
		if (is_operator(line[i]))
		{
			int strt = i;
			str = ft_malloc(sizeof(char) * ft_lenoperator(line, &i) + 1, 1);
			strncpy(str, line + strt, i - strt);
			str[i -strt] = '\0';
			spliter[index++] = str;
		}
		else
		{
			int start = i;
			skip_whiteword(line, &i);
			str = ft_malloc(i - start + 1, 1);
			strncpy(str, line + start, i - start);
			str[i - start] = '\0';
			spliter[index++] = str;
		}
	}
	spliter[index] = NULL;
	data_struc()->size = index;
	return spliter;
}
