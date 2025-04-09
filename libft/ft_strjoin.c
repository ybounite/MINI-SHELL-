/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:39:57 by ybounite          #+#    #+#             */
/*   Updated: 2024/10/29 19:39:59 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	contr;
	size_t	i;
	size_t	totalen;

	if (!s1 || !s2)
		return (NULL);
	contr = 0;
	i = 0;
	totalen = ft_strlen(s2) + ft_strlen(s1);
	tab = malloc((totalen + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[contr])
		tab[i++] = s1[contr++];
	contr = 0;
	while (s2[contr])
		tab[i++] = s2[contr++];
	tab[i] = '\0';
	return (tab);
}
