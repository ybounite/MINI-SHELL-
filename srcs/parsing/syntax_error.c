/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:24:47 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 15:41:52 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	is_first_operation_pipe(char *str)
{
	int	i;

	i = 0;
	ft_skip_whitespace(str, &i);
	if (str[i] == PIPE)
		ft_puterror('|');
	return (str[i] == '|');
}

char	*get_token_symbol(int type)
{
	if (type == INPUT_REDIRECTION)
		return ("<");
	else if (type == OUTPUT_REDIRECTION)
		return (">");
	else if (type == APPEND_REDIRECTION)
		return (">>");
	else if (type == HERE_DOCUMENT)
		return ("<<");
	else if (type == PIPE)
		return ("|");
	else
		return ("newline");
}

int	ft_lenword(char *str)
{
	int (len), (i);
	(1) && (len = 0), (i = 0);
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (str[i] && isquotes(str[i]))
		{
			if (lenqoutes(str, &i) < 0)
				return (-1);
		}
		else if (str[i] && is_operator(str[i]))
			i++;
		else
		{
			while (str[i] && !is_operator(str[i]) && !isquotes(str[i])
				&& !find_space(str[i]))
			{
				if (i - 1 > 0 && find_space(str[i - 1]))
					len++;
				i++;
				len++;
			}
		}
	}
	return (len);
}
