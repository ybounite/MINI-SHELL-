/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/07 14:28:42 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst	*list;
	t_env_lst	*original_list;
	t_env_lst	*temp;

	list = NULL;
	if (handler_syntax_error(st_string->line))
		return (data_struc()->exit_status = 2, 0);
	st_string->tokens = spliter(st_string->line);
	if (!st_string->tokens)
		return (false);
	tokenize(st_string->tokens, &list);
	print_lst_tokens(list); // delet
	if (ft_isheredoc(list))
		handler_heredoc(list);
	// -------------------------- Test variable expansion----------------------------------------
	printf("--- Testing Variable Expansion ---\n");
	original_list = list;
	// before
	printf("Before expansion:\n");
	temp = original_list;
	while (temp)
	{
		printf("Token: [%s] Type: %d\n", temp->value, temp->type);
		temp = temp->next;
	}
	expand_variables(list);
	// after
	printf("\nAfter expansion:\n");
	temp = list;
	while (temp)
	{
		printf("Token: [%s] Type: %d\n", temp->value, temp->type);
		temp = temp->next;
	}
	printf("--- End of Expansion Test ---\n");
	// -------------------------- Test variable expansion----------------------------------------
	ft_destroylist(list);
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
