/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:13:35 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/14 10:58:10 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_single_quote(char *result, const char *str, int *i, bool *in_sq)
{
	char	*temp;

	*in_sq = !*in_sq;
	temp = result;
	result = ft_strjoin_char(result, str[*i]);
	printf("singles       result : %s\n", result);
	(*i)++;
	return (result);
}

char	*handle_double_quote(char *result, const char *str, int *i, bool *in_dq)
{
	char *temp;

	*in_dq = !*in_dq;
	temp = result;
	result = ft_strjoin_char(result, str[*i]);
	(*i)++;
	return (result);
}