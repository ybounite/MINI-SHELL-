/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whit_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:33:07 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 15:18:53 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_strqoutes(char *str, int *inedx, char quotes)
{
	int		counter;

	counter = 0;
	while (str[*inedx] && str[*inedx] != quotes)
	{
		(*inedx)++;
		counter++;
	}
	if (str[*inedx] == '\0')
		return (ft_puterror(quotes), -1337);
	if (str[*inedx] && str[*inedx] == quotes)
	{
		(*inedx)++;
		counter++;
	}
	return (counter);
}

void	skip_whiteword(char *str, int *i)
{
	char	qouts;

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

void	ft_skip_qutes(char *str, int *start, int *len)
{
	char	qoutes;

	qoutes = str[(*start)++];
	while (str[*start] && str[*start] != qoutes)
	{
		(*start)++;
		(*len)++;
	}
	(*start)++;
}
