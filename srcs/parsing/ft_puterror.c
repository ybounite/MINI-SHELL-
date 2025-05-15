/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:41:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 15:41:52 by ybounite         ###   ########.fr       */
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

void	ft_error(en_status type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(get_token_symbol(type), 2);
	ft_putendl_fd("'", 2);
}
