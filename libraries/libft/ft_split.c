/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:50:31 by bamezoua          #+#    #+#             */
/*   Updated: 2024/11/05 18:20:36 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	count;
	int	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strcpy(char const *s, char c)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_free(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		free(str[j]);
		j++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		j;

	if (s == NULL)
		return (NULL);
	j = 0;
	str = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			str[j] = ft_strcpy(&*s, c);
			if (!str[j])
				return (ft_free(str), NULL);
			j++;
			while (*s && *s != c)
				s++;
		}
	}
	str[j] = NULL;
	return (str);
}
