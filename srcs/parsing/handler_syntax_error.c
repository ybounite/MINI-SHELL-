/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:24:12 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 15:40:45 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	redirection_target_error(t_env_lst *curr)
{
	if (!curr->next)
		ft_error(1);
	else
		ft_error(curr->next->type);
	return (false);
}

bool	is_redirection(int type)
{
	return (type == INPUT_REDIRECTION || type == OUTPUT_REDIRECTION
		|| type == APPEND_REDIRECTION);
}

bool	is_invalid_cmd_type(t_env_lst *token)
{
	return (token->type != CMD && token->type != HERE_DOCUMENT
		&& token->type != DOUBLE_QUOTE && token->type != SINGLE_QUOTE);
}

bool	check_syntax_errors(t_env_lst *tokens)
{
	t_env_lst	*curr;
	t_env_lst	*prev;

	(1) && (curr = tokens), (prev = NULL);
	while (curr)
	{
		if (is_redirection(curr->type) && curr->next
			&& is_redirection(curr->next->type))
		{
			ft_error(curr->next->type);
			return (false);
		}
		if (curr->type == PIPE)
		{
			if (!curr->next || curr->next->type == PIPE)
				return (ft_error(PIPE), false);
		}
		if (is_redirection(curr->type) && (!curr->next
				|| is_invalid_cmd_type(curr->next)))
			return (redirection_target_error(curr));
		prev = curr;
		curr = curr->next;
	}
	return (true);
}

bool	handler_syntax_error(char *line)
{
	if (is_first_operation_pipe(line)
		|| ft_lenword(line) < 0)
		return (true);
	return (false);
}
