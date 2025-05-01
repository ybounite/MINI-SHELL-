/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:48:04 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/01 08:42:48 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substring(char *str, int start , int len)
{
	int		i;
	char 	*ptr;
	i = 0;
	ptr = malloc(len + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	while (str[start] && i < len)
	{
		if (!isquotes(str[start]))
			ptr[i++] = str[start];
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_spliter(t_env_lst **list, char *line)
{
	en_status	stats;
	int			i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		while (line[i] && line[i] == SPACE)
			i++;
		stats = get_token_type_from_char(line[i]);
		if (stats == CMD)
			handler_words(list, line, &i, stats);
		else if (stats == SINGLE_QUOTE || stats == DOUBLE_QUOTE)
			handler_qoutes(list, line, &i, stats);
		else if (stats == PIPE || stats == REDIRECTION)
			handler_operator(list, line, &i, stats);
		else if (stats == DOLLAR)
			heandler_dollar(list, line, &i, stats);
	}
}
