/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:32:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/12 18:36:24 by ybounite         ###   ########.fr       */
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

int	read_and_process_heredoc_input(char *delimiter, bool expand)
{
	char	*line;
	char	*str_expand;

	while (true)
	{
		line = readline("> ");
		if (!line)
			return (error_herdoc(delimiter), data_struc()->exit_status = 0, 1);
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

void	sigint_handler(int va_signal)
{
	if (va_signal == SIGINT)
	{
		
		rl_free_line_state();
		rl_cleanup_after_signal();
		close(data_struc()->heredoc_fd);
		ft_malloc(false, false);
		signal(SIGINT, SIG_DFL);
		exit(130);
	}
}

void	handle_child_exit_status(int status)
{
	if (WEXITSTATUS(status) == 130)
	{
		data_struc()->exit_status = WEXITSTATUS(status);
		data_struc()->is_error = true;
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
		signal(SIGINT, sigint_handler);
		read_and_process_heredoc_input(delimiter, dolar);
		close(data_struc()->heredoc_fd);
		ft_malloc(false, 0);
		exit(0);
	}
	waitpid(pid, &status, 0);
	handle_child_exit_status(status);
	return (true);
}

int	handler_heredoc(t_env_lst	*list)
{
	char	*delimiter;
	int		is_expand;

	delimiter = NULL;
	is_expand = 0;
	ft_clculate_heredoc(list);
	while (list)
	{
		if (list->type == HERE_DOCUMENT && list->next)
		{
			list->value = ft_strdup("<");
			list = list->next;
			delimiter = find_delimiter(list, &is_expand);
			data_struc()->heredoc_fd = open_heredoc();
			if (data_struc()->heredoc_fd < 0)
				return (data_struc()->exit_status = 2, 0);
			handle_forked_process(delimiter, is_expand);
			list->value = data_struc()->heredoc_file;
			if (data_struc()->is_error)
				break ;
		}
		list = list->next;
	}
	// printf("%s<-> is  Error for herdoc %d<->\e[0m\n", YELLOW, data_struc()->is_error);
	return (true);
}
