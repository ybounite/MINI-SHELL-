/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:23:31 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/27 16:24:51 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lendollar(char *str, int start)
{
	int len;

	len = 0;
	if (str[start] == '?')
		return (++len);
	while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))// $""
	{
		start++;
		len++;
	}
	return (len);
}


void	heandler_dollar(t_env_lst **list, char *str, int *i, en_status state)
{
	char	*ptr;
	int		index;
	int		len;

	(index = 0), ((*i)++);
	if (isquotes(str[*i]))
		(*i)++;
	len = lendollar(str, *i);
	if (len < 0)
		return ;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return ;
	while (index < len && str[*i])
		ptr[index++] = str[(*i)++];
	ptr[index] = '\0';
	if (isquotes(str[*i]))
		(*i)++;
	ft_add_newtoken(list, ptr, state);
}
