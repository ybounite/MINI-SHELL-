/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utlis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:01:49 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/17 14:35:00 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_operator(char c)
{
	return (c == '&' || c == '|' || c == '>'
			|| c == '<' || c == '(' || c == ')');
}

bool	find_space(char c)
{
	return (c == SPACE || c == TAB || c == NEWLINE);
}

bool	isquotes(char c)
{
	return (c == '\'' || c == '\"');
}

void	ft_skip_whitespace(char *str, int *index)
{
	while (str[*index] && find_space(str[*index]))
		(*index)++;
}
