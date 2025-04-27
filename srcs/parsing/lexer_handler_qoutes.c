/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_qoutes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:49:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/27 16:28:52 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lenofwords_qoutes(char *str, int start)
{
	int		len;
	char	qoutes;
	len = 0;
	while (str[start] && str[start] != SPACE)
	{
		if (isquotes(str[start]))
		{
			qoutes = str[start++];
			while (str[start] && str[start] != qoutes)
			{
				start++;
				len++;
			}
			start++;
		}
		else
		{
			while (str[start] && !isquotes(str[start]) && str[start] != SPACE)
			{
				start++;
				len++;	
			}
		}
	}
	return (len);
}

void	handler_qoutes(t_env_lst **list, char *str, int *i,
	en_status state)
{
	char	*ptr;
	char	quotes;
	int		index;
	int		len;

	(1) && (index = 0), (len = lenofwords_qoutes(str, *i));
	if (len == 0)
	{
		ft_add_newtoken(list, ft_strdup("\"\""), state);
		(*i) += 2;
		return ;
	}
	if (str[*i] == DOUBLE_QUOTE && str[*i + 1] == DOLLAR)
	{
		index = *i;
		heandler_dollar(list, str, &index, DOLLAR);
		*i = index;
		return ;
	}
	ptr = malloc(len + 1 * sizeof(char));
	if (!ptr)
		return ;
	while (str[*i] && index < len)
	{
		if (isquotes(str[*i]))
		{
			quotes = str[(*i)++];
			while (str[*i] && str[*i] != quotes)
				ptr[index++] = str[(*i)++];
			(*i)++;
		}
		else
		{
			while (str[*i] && !isquotes(str[*i]) && str[*i] != SPACE)
				ptr[index++] = str[(*i)++];
		}
	}
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}
