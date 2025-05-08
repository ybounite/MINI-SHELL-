/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/08 19:39:55 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_env_lst	*list, t_env_lst 	**head)
{
	en_status	stats;
	char		*str;

	while (list)
	{
		if (is_quotes_thes_str(list->value))
			str = ft_remove_quotes(list->value);
		else
			str = list->value;
		stats =  get_token_type(list->value);
		ft_add_newtoken(head, str, stats);
		list = list->next;
	}
}

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst	*list;

	list = NULL;
	if (handler_syntax_error(st_string->line))
		return (data_struc()->exit_status = 2, 0);
	st_string->tokens = spliter(st_string->line);
	if (!st_string->tokens)
		return (false);
	tokenize(st_string->tokens, &list);
	data_struc()->head = list;
	if (ft_isheredoc(list))
		handler_heredoc(list);
	expand_variables(list);
	// print_lst_tokens(list); // delet
	t_env_lst *head = NULL;
	remove_quotes(list, &head);
	// printf("\n%s<->      after remove quotes     <->\e[0m\n", GREEN);
	st_string->head = head;
	print_lst_tokens(list);
	execute_command(st_string);
	return (true);
}

void	start_shell_session(t_string st_string)
{
	while (true)
	{
		st_string.line = get_line();
		handle_input_syntax(&st_string);
	}
}
