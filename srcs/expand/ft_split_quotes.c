/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:13:26 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 17:13:41 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	skip_word(const char *s, char sep)
{
	int i = 0;
	char quote = 0;

	while (s[i] && (s[i] != sep || quote))
	{
		if (is_quote(s[i]))
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		i++;
	}
	return (i);
}

static int	count_words(const char *s, char sep)
{
	int count = 0, i = 0, len;

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
	char *res = ft_malloc(len + 1, 1);
	for (int i = 0; i < len; i++)
		res[i] = s[i];
	res[len] = '\0';
	return (res);
}

char	**ft_split_quotes(const char *s, char sep)
{
	int i = 0, w = 0, len;
	char **res;

	if (!s)
		return (NULL);
	res = ft_malloc(sizeof(char *) * (count_words(s, sep) + 1), 1);
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i])
		{
			len = skip_word(&s[i], sep);
			res[w++] = copy_word(&s[i], len);
			i += len;
		}
	}
	res[w] = NULL;
	return (res);
}
