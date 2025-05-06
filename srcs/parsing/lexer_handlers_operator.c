/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:44 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/05 16:34:58 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_operator(t_env_lst **list, char *str, int *i, en_status state)
{
	int		index;
	char	*ptr;

	index = 0;
	ptr = ft_malloc(3 * sizeof(char), 1);
	if (!ptr)
		return ;
	while (str[*i] && str[*i] != SPACE)
		ptr[index++] = str[(*i)++];
	ptr[index] = '\0';
	if (state == REDIRECTION)
		state = get_redirection_type_from_str(ptr);
	ft_add_newtoken(list, ptr, state);
}
// delet 
// void	handler_parenthesis(t_env_lst **list, char *str, int *i,
// 	en_status state)
// {
// 	int		index;
// 	char	charcter;
// 	char	*ptr;

// 	charcter = str[*i];
// 	index = 0;
// 	ptr = malloc(lentword(str, *i) + 1);
// 	while (str[*i] && str[*i] != ')')
// 		ptr[index++] = str[(*i)++];
// 	ptr[index++] = ')';
// 	ptr[index] = '\0';
// 	(*i)++;
// 	ft_add_newtoken(list, ptr, state);
// }
