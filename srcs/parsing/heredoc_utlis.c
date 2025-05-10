/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:36:52 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 10:09:30 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_isheredoc(t_env_lst *list)
{
	while (list)
	{
		if (list->type == HERE_DOCUMENT)
			return (true);
		list = list->next;
	}
	return (false);
}

bool	is_quotes_thes_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isquotes(str[i]))
			return (true);
		i++;
	}
	return (false);
}

int	ft_lenofwords(char *str)
{
	char	qoutes;
	int		len;
	int		start;

	len = 0;
	start = 0;
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

char	*ft_remove_quotes(char *str)
{
	char	*ptr;
	char	quotes;
	int		index;
	int		i;

	(1) && (i = 0) , (index = 0);
	ptr = ft_malloc(ft_lenofwords(str) + 1, 1);
	while (str[i] && index < ft_lenofwords(str))
	{
		if (isquotes(str[i]))
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				ptr[index++] = str[i++];
			if (isquotes(str[i]))
				i++;
		}
		else
		{
			while (str[i] && !isquotes(str[i]) && str[i] != SPACE)
				ptr[index++] = str[i++];
		}
	}
	ptr[index] = '\0';
	return (ptr);
}

char	*find_delimiter(t_env_lst *list, int *is_expand)
{
	char	*delimiter;
	if (!is_quotes_thes_str(list->value))
		*is_expand = 1;
	delimiter = ft_remove_quotes(list->value);
	return (delimiter);
}
