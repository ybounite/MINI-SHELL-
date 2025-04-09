/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:41:40 by ybounite          #+#    #+#             */
/*   Updated: 2024/10/29 19:41:43 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;
	size_t	d;

	i = 0;
	if (dstsize == 0 && dst == NULL && src != NULL)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	d = dstlen;
	if (dstsize == 0 || dstsize <= dstlen)
		return (dstsize + srclen);
	while (i < (dstsize - dstlen - 1) && src[i] != '\0')
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	dst[d] = '\0';
	return (dstlen + srclen);
}
