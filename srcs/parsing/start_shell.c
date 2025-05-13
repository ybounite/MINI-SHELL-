/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/13 11:09:55 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	singel_quote(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	while (str[i])
	{
		if (isquotes(str[i]))
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				i++;
			if (str[i])
				i++;
			else
				return (false);
		}
		else
			i++;
	}
	return (true);
}

void	remove_quotes(t_env_lst *list, t_env_lst **head)
{
	en_status	stats;
	char		*str;

	while (list)
	{
		if (is_quotes_thes_str(list->value) && singel_quote(list->value))
			str = ft_remove_quotes(list->value);
		else
			str = list->value;
		stats = get_token_type(list->value);
		ft_add_newtoken(head, str, stats);
		list = list->next;
	}
}

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst	*list;
	t_env_lst	*head;

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
	if (expand_variables(&list) == -1)
		return (data_struc()->exit_status = 1, 1);
	else
		data_struc()->exit_status = 0;
	// print_lst_tokens(list); // delet
	head = NULL;
	remove_quotes(list, &head);
	// printf("\n%s<->      after remove quotes     <->\e[0m\n", YELLOW);
	st_string->head = head;
	execute_command(st_string);
	// print_lst_tokens(head);
	return (true);
}

void	start_shell_session(t_string st_string)
{
	while (true)
	{
		data_struc()->is_error = 0;
		st_string.line = get_line();
		handle_input_syntax(&st_string);
	}
}
