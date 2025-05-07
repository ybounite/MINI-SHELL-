/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/07 20:00:00 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(char **tokens, t_env_lst 	**head)
{
	en_status	stats;
	char		*str;
	int 		i;

	i = 0;
	while (tokens[i])
	{
		if (is_quotes_thes_str(tokens[i]))
			str = ft_remove_quotes(tokens[i]);
		else
			str = tokens[i];
		stats =  get_token_type(tokens[i]);
		ft_add_newtoken(head, str, stats);
		i++;
	}
}

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst	*list;
	// t_env_lst	*original_list;

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
	// original_list = list;
	expand_variables(list);
	print_lst_tokens(list); // delet
	t_env_lst *head = NULL;
	remove_quotes(st_string->tokens, &head);
	printf("\n%s<->      after remove quotes     <->\e[0m\n", GREEN);
	print_lst_tokens(head); // delet
	ft_destroylist(list);
	ft_destroylist(head);// delet
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
