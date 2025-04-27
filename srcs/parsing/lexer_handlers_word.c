/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:06:24 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/27 16:07:06 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	lentword(char *str, int start)
{
	int		len;
	char	qouts;

	(1) && (len = 0), (qouts = 0);
	while (str[start] && str[start] != SPACE)
	{
		if (isquotes(str[start]))
		{
			qouts = str[start++];
			while (str[start] && str[start] != qouts)
			{
				start++;
				len++;
			}
			start++;
		}
		else
		{
			start++;
			len++;
		}
	}
	return (len);
}

void	handler_words(t_env_lst **list, char *str, int *i, en_status state)
{
	int		index;
	char	*ptr;
	int		len;
	char	qouts;
	(1) && (index = 0), (len = lentword(str, *i));
	if (len == 0)
		return ;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return ;
	while (str[*i] && str[*i] != SPACE)
	{
		if (isquotes(str[*i]))
		{
			qouts = str[(*i)++];
			while (str[*i] && str[*i] != qouts)
				ptr[index++] = str[(*i)++];
			(*i)++;
		}
		else
			ptr[index++] = str[(*i)++];
	}
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}
