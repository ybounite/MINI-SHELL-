/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:13:26 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 18:09:45 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	skip_word(const char *str, char sep)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && (str[i] != sep || quote))
	{
		if (is_quote(str[i]))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	return (i);
}

static int	count_words(const char *s, char sep)
{
	int (count), (i), (len);
	(1) && (count = 0), (i = 0), (len = 0);
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i])
		{
			len = skip_word(&s[i], sep);
			i += len;
			count++;
		}
	}
	return (count);
}

static char	*copy_word(const char *s, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_malloc(len + 1, 1);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

char	**ft_split_quotes(const char *str, char sep)
{
	int		i;
	int		len;
	int		index;
	char	**res;

	(1) && (i = 0), (index = 0);
	if (!str)
		return (NULL);
	res = ft_malloc(sizeof(char *) * (count_words(str, sep) + 1), 1);
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
		{
			len = skip_word(&str[i], sep);
			res[index++] = copy_word(&str[i], len);
			i += len;
		}
	}
	res[index] = NULL;
	return (res);
}
