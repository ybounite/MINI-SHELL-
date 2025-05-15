/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:32:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 14:50:15 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_heredoc(t_env_lst *list)
{
	while (list)
	{
		if (list->type == HERE_DOCUMENT)
			return (true);
		list = list->next;
	}
	return (false);
}

char	*ft_expand(char *line)
{
	if (*line == '$' && isquotes((*line + 1)))
		return (line);
	else
		return (expand_heredoc(line));
}

bool	is_invalid_heredoc_syntax(t_env_lst *list)
{
	if (!list->next || list->next->type != CMD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!list->next)
			ft_putendl_fd("newline'", 2);
		else
		{
			ft_putstr_fd(get_token_symbol(list->next->type), 2);
			ft_putendl_fd("'", 2);
		}
		g_exit_status = 2;
		data_struc()->is_error = true;
		return (true);
	}
	return (false);
}

int	handler_heredoc(t_env_lst *list)
{
	char	*delimiter;
	int		is_expand;

	(1) && (delimiter = NULL), (is_expand = 0);
	ft_clculate_heredoc(list);
	while (list)
	{
		if (list->type == HERE_DOCUMENT)
		{
			if (is_invalid_heredoc_syntax(list))
				return (false);
			list->value = ft_strdup("<");
			list = list->next;
			delimiter = find_delimiter(list, &is_expand);
			data_struc()->heredoc_fd = open_heredoc();
			if (data_struc()->heredoc_fd < 0)
				return (g_exit_status = 2, 0);
			handle_forked_process(delimiter, is_expand);
			list->value = data_struc()->heredoc_file;
			if (data_struc()->is_error)
				break ;
		}
		list = list->next;
	}
	return (true);
}
