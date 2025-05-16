/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/16 09:21:57 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst (*list);
	t_env_lst (*head);
	(1) && (list = NULL), (head = NULL);
	st_string->tokens = spliter(st_string->line);
	if (!st_string->tokens)
		return (false);
	tokenize(st_string->tokens, &list);
	if (!list)
		return (true);
	if (!check_syntax_errors(list))
		return (g_exit_status = 2, false);
	data_struc()->head = list;
	if (ft_isheredoc(list))
		handler_heredoc(list);
	if (data_struc()->is_error)
		return (false);
	if (expand_variables(&list) == -1)
		return (g_exit_status = 1, false);
	else
		g_exit_status = 0;
	remove_quotes(list, &head);
	st_string->head = head;
	execute_command(st_string);
	return (true);
}

void	start_shell_session(t_string st_string)
{
	while (true)
	{
		data_struc()->is_empty = 0;
		data_struc()->is_error = 0;
		st_string.line = get_line();
		if (handler_syntax_error(st_string.line))
		{
			g_exit_status = 1;
			continue ;
		}
		handle_input_syntax(&st_string);
	}
}
