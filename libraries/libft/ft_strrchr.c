/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:52:44 by bamezoua          #+#    #+#             */
/*   Updated: 2024/11/04 10:52:46 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ff;
	int				i;
	unsigned char	b;

	ff = (char *)s;
	b = (unsigned char)c;
	i = ft_strlen(ff);
	if (b == '\0')
		return (ff + i);
	while (i > 0)
	{
		if (ff[i - 1] == b)
			return (ff + i - 1);
		i--;
	}
	return (NULL);
}
