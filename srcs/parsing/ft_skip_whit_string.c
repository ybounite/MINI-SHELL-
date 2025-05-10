/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whit_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:33:07 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 10:29:21 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	ft_skip_whitquotes(char *str, int *index)
{
	char	quote;

	quote = str[(*index)++];
	while (str[*index] && str[*index] != quote)
		(*index)++;
	if (str[*index])
		(*index)++;
	return ('Q');
}

char	ft_skip_whitoperator(char *str, int *index)
{
	(*index)++;
	while (str[*index] && is_operator(str[*index]))
		(*index)++;
	return ('O');
}

char	ft_skip_whitword(char *str, int *index)
{
	while (str[*index] && !is_operator(str[*index])
		&& !isquotes(str[*index]) && !find_space(str[*index]))
		(*index)++;
	return ('W');
}

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
