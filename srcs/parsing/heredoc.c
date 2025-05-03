/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:32:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/03 15:36:08 by ybounite         ###   ########.fr       */
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

int	handle_heredoc(char *delimiter, int *heredoc_fd)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	*heredoc_fd = pipe_fd[0];
	return (1);
}

int	hase_heredoc_rediraection(t_env_lst *head)
{
	t_env_lst	*current;
	char		*delimiter;
	
	current = head;
	delimiter = NULL;
	while (current)
	{
		if (current->type == HERE_DOCUMENT && current->next)
		{
			delimiter = current->next->value;
			if (!delimiter)
				return (0);
			if (!handle_heredoc(delimiter, &data_struc()->heredoc_fd))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
