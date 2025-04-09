/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:19:56 by ybounite          #+#    #+#             */
/*   Updated: 2024/10/29 19:20:09 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (!d && !s)
		return (NULL);
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
