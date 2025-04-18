/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:51:16 by bamezoua          #+#    #+#             */
/*   Updated: 2024/11/04 10:51:18 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	b;
	char	*str;

	str = (char *)s;
	b = (char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == b)
			return (&str[i]);
		i++;
	}
	if (b == '\0')
		return (&str[i]);
	return (NULL);
}
