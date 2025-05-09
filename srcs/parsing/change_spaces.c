/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:13:41 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/09 19:14:46 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

char	*collapse_spaces(const char *str)
{
	int		i;
	int		j;
	int		space_flag;
	char	*result;

	(1) && (i = 0), (j = 0), (space_flag = 0);
	result = ft_malloc(ft_strlen(str) + 1, true);
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			if (!space_flag)
				result[j++] = ' ';
			space_flag = 1;
		}
		else
		{
			result[j++] = str[i];
			space_flag = 0;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
