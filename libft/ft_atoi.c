/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:58:40 by ybounite          #+#    #+#             */
/*   Updated: 2025/01/28 09:03:18 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		sun;

	sun = 1;
	nbr = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sun *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (10 * nbr) + (str[i] - 48);
		if (nbr < 0)
			return (-sun * (sun == 1));
		i++;
	}
	return ((int)nbr * sun);
}
