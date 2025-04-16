/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:47:50 by bamezoua          #+#    #+#             */
/*   Updated: 2024/11/08 09:44:17 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	b;

	i = 0;
	str = (unsigned char *)s;
	b = (unsigned char)c;
	while (n > i)
	{
		if (str[i] == b)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
