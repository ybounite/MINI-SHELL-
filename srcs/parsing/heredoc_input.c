/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:40:56 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 14:47:04 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_and_process_heredoc_input(char *delimiter, bool expand)
{
	char	*line;
	char	*str_expand;

	while (true)
	{
		line = readline("> ");
		if (!line)
			return (error_herdoc(delimiter), g_exit_status = 0, 1);
		if (!ft_strcmp(line, delimiter))
			return (free(line), 1);
		if (expand)
		{
			str_expand = ft_expand(line);
			write(data_struc()->heredoc_fd, str_expand, ft_strlen(str_expand));
		}
		else
			write(data_struc()->heredoc_fd, line, ft_strlen(line));
		write(data_struc()->heredoc_fd, "\n", 1);
		free(line);
	}
	return (true);
}

void	handle_child_exit_status(int status)
{
	if (WEXITSTATUS(status) == 130)
	{
		g_exit_status = WEXITSTATUS(status);
		data_struc()->is_error = true;
	}
	if (WIFEXITED(status))
	{
		g_exit_status = 128 + WEXITSTATUS(status);
		if (g_exit_status == 128)
			data_struc()->signals_flag = 2;
		else if (g_exit_status == 258)
			data_struc()->signals_flag = 1;
	}
}

int	handle_forked_process(char *delimiter, bool dolar)
{
	pid_t	pid;
	int		status;
	int		signal_number;

	pid = fork();
	signal_number = 0;
	if (pid == -1)
		return (perror("minishell: fork"), 1);
	else if (pid == 0)
	{
		signal(SIGINT, set_signals_for_heredoc);
		read_and_process_heredoc_input(delimiter, dolar);
		close(data_struc()->heredoc_fd);
		ft_malloc(false, 0);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handler);
	handle_child_exit_status(status);
	return (true);
}
