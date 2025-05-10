/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:44 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 09:22:22 by ybounite         ###   ########.fr       */
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
