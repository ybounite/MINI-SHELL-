/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:24:47 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/09 18:31:33 by ybounite         ###   ########.fr       */
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

bool	is_first_operation_pipe(char *str)
{
	int i = 0;
	ft_skip_whitespace(str, &i);
	if (str[i] == PIPE)
		ft_puterror('|');
	return (str[i] == '|');
}

bool	is_last_operation_pipe(char *str)
{
	int		i;
	char	last_token_type;
	(1) && (i = 0), (last_token_type = 0);
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (!str[i])
			break;
		if (isquotes(str[i]))
			last_token_type = ft_skip_whitquotes(str, &i);
		else if (str[i] == PIPE)
		{
			i++;
			last_token_type = '|';
		}
		else if (is_operator(str[i]))
			last_token_type = ft_skip_whitoperator(str, &i);
		else
			last_token_type = ft_skip_whitword(str, &i);
	}
	if (last_token_type == '|')
		ft_puterror('|');
	if (last_token_type == 'O')
		ft_puterror('\n');
	return (last_token_type == 'O' || last_token_type == '|');
}


int	ft_lenword(char *str)
{
	int	(quote_len), (len), (i);
	(1) && (len = 0), (i = 0);
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (str[i] && isquotes(str[i]))
		{
			quote_len = lenqoutes(str, &i);
			if (quote_len < 0)
				return (-1);
			len += quote_len;
		}
		else if (str[i] && is_operator(str[i]))
			len += lenoperator(str, &i);
		else
		{
			while (str[i] && !is_operator(str[i]) && !isquotes(str[i])
				&& !find_space(str[i]))
			{
				if (i - 1 > 0 && find_space(str[i - 1]))
					len++;
				i++;
				len++;
			}
		}
		if (len < 0)
			break ;
	}
	return (len);
}
