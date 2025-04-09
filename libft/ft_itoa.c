/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:52:07 by ybounite          #+#    #+#             */
/*   Updated: 2024/11/03 12:30:01 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	size_t	lenofinteger(long nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (len + 1);
	else if (nbr < 0)
	{
		len++;
		nbr *= -1;
	}
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	char	*ptr;
	long	nbr;

	nbr = n;
	len = lenofinteger(nbr);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (nbr < 0)
	{
		ptr[0] = '-';
		nbr *= -1;
	}
	i = len - 1;
	while (nbr >= 10)
	{
		ptr[i--] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (nbr <= 9)
		ptr[i] = nbr + 48;
	ptr[len++] = '\0';
	return (ptr);
}
