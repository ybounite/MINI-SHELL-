/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:41:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/16 14:41:37 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_puterror(char error)
{
	ft_putstr_fd("minishell: parse error near `", 2);
	if (error == '\n')
		ft_putstr_fd("newline", 2);
	else
		write(2, &error, 1);
	write(2, "\'\n", 2);
	data_struc()->is_error = 1;
}

void	ft_error(t_status type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(get_token_symbol(type), 2);
	ft_putendl_fd("'", 2);
}

int	ft_iserror(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	return (i != 0);
}
