/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 07:46:24 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/17 14:34:54 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// Error > file Error.c
void	ft_error_quotes(char quotes)
{
	printf("minishell: parse error near `%c\'\n", quotes);
	data_struc()->is_error = 1;
}

int	skip_strqoutes(char *str, int *inedx, char quotes)
{
	int	counter;

	counter = 0;
	while (str[*inedx] && str[*inedx] != quotes)
	{
		// if (str[*inedx] == '\\' && str[*inedx + 1] == quotes)
		(*inedx)++;
		counter++;
	}
	if (str[*inedx] == '\0')// ERROR();
		return (ft_error_quotes(quotes), -1337);
	if (str[*inedx] && str[*inedx] == quotes)
	{
		(*inedx)++;
		counter++;
	}
	return (counter);
}

int	lenqoutes(char *str, int *i)
{
	char	quotes;
	int		counter;
	int		start;

	counter = 0;
	if (*i - 1 > 0 && find_space(str[*i - 1]))
		counter++;
	quotes = str[(*i)++];
	start = *i;
	counter += skip_strqoutes(str, &start, quotes) + 1;
	*i = start;
	return (counter);
}

int	lenoperator(char *str, int *i)
{
	int		counter;
	char	operator;

	counter = 0;
	operator = str[*i];//save operator
	while (str[*i] && str[*i] == operator)
	{
		if (str[*i + 1] && operator == '>' && str[*i + 1] == '<')
			return (ft_error_quotes(operator), -1337);
		else if (str[*i + 1] && operator == '<' && str[*i + 1] == '>')
			return (printf("minishell : parse error near `\\n'\n"), -1337);
		counter++;
		(*i)++;
		if (counter >= 3)
			return (ft_error_quotes(operator), -1337);
	}
	counter++;// add space after operator 
	if (str[*i] && !find_space(str[*i]))
		counter++;
	return (counter);
}

int	ft_lenword(char *str)
{
	int (len), (i);
	len = 0;
	i = 0;
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (str[i] && isquotes(str[i]))
			len += lenqoutes(str, &i);
		else if (str[i] && is_operator(str[i]))
			len += lenoperator(str, &i);
		else
		{
			while (str[i] && !is_operator(str[i])
				&& !isquotes(str[i]) && !find_space(str[i]))
			{
				if (i - 1 > 0 && find_space(str[i - 1]))
					len++;
				i++;
				len++;
			}
		}
		if (len < 0)
			break ;
	}
	return (len);
}
