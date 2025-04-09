/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satart_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:35:02 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/09 07:04:35 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line()
{
	char *line;

	line = readline(MINISPELL);
	if (!line)
	{
		printf("exit\n");
		rl_clear_history();
		exit(0);
	}
	if (line)
		add_history(line);
	return (line);
}
bool	is_builtins(char *str)
{
	return (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
			|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
			|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env") || !ft_strcmp(str, "exit"));
}

int	handle_builtins(t_env_lst **head, en_status_type stats)
{
	t_env_lst *tmp;
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	if (is_builtins(tmp->value))
		tmp->type = BUILTINS;
	return 1;
}

int	handle_input_syntax(char *input)
{
	en_status_type	type;
	t_env_lst		*head = NULL;
	int 			index;

	index = 0;
	while(input[index])
	{
		ft_skip_whitespace(input, &index);
		type = find_type_state(input[index]);
		if (type == CMD)
			handler_words(&head, input, &index);
		else if (type == check_stats_type(input+index))
			handler_other_operator(&head, input, &index, type);
		else if (type == DOUBLE_QUOTE || type == SINGLE_QUOTE)
			handler_quotes(&head, input, &index);
		if (type == CMD)
			handle_builtins(&head, BUILTINS);
		// else if (type == PARENTHESIS)
		// 	handler_parenthesis(&head, input, &index, type);
		ft_skip_whitespace(input, &index);
	}
	print_lst_tokens(head);
	free_list(head);
	return 1;
}

// int	start_shell_session(t_string input)
// {
// 	t_env_lst	*list;
// 	// printf("%d\n",   data_struc()->exit_status);
// 	while (1)
// 	{
// 		input.line = get_line();
// 		handle_input_syntax(input.line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }

