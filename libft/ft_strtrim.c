/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:30:11 by ybounite          #+#    #+#             */
/*   Updated: 2024/10/29 20:30:12 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	to_find(char const *set, char shar)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == shar)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*tab;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (to_find(set, s1[i]))
		i++;
	if (i == len + 1)
		return (ft_strdup(""));
	while (to_find(set, s1[len]))
		len--;
	tab = ft_substr(s1, i, (len + 1) - i);
	return (tab);
}
