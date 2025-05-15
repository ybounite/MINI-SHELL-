/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:19:05 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 15:56:39 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	singel_quote(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	while (str[i])
	{
		if (isquotes(str[i]))
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				i++;
			if (str[i])
				i++;
			else
				return (false);
		}
		else
			i++;
	}
	return (true);
}

void	remove_quotes(t_env_lst *list, t_env_lst **head)
{
	t_status	stats;
	char		*str;

	while (list)
	{
		if (is_quotes_thes_str(list->value) && singel_quote(list->value))
			str = ft_remove_quotes(list->value);
		else
			str = list->value;
		stats = get_token_type(list->value);
		ft_add_newtoken(head, str, stats);
		list = list->next;
	}
}
