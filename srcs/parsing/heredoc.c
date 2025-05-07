/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:32:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/07 09:47:54 by ybounite         ###   ########.fr       */
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

void	error_herdoc(char *delimiter)
{
	static int i;

	i = 1;
	ft_putstr_fd("minishell : here-document at line", 2);
	printf(" %d ", i++);
	printf("delimited by end-of-file (wanted `%s')\n", delimiter);
}

int	read_and_process_heredoc_input(char *delimiter, bool expand)
{
	char	*line;
	// char	*str_expand;

	while (true)
	{
		line = readline("> ");
		if (!line)
			error_herdoc(delimiter);
		if (!ft_strcmp(line, delimiter))
			return (free(line), 1);
		// if (expand)
		// {
		// 	str_expand = ft_expand(line);
		// 	write(data_struc()->heredoc_fd, str_expand, strlen(str_expand));
		// }
		// else
		(void)expand;
		write(data_struc()->heredoc_fd, line, strlen(line));
		write(data_struc()->heredoc_fd, "\n", 1);
		free(line);
	}
	return (true);
}

int	handle_forked_process(char *delimiter, bool dolar)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		// signal(SIGINT, sigint_handler);// handler signal 
		read_and_process_heredoc_input(delimiter, dolar);
		close(data_struc()->heredoc_fd);
		ft_malloc(false, 0);
		ft_destroylist(data_struc()->head);
		exit(0);
	}
	waitpid(pid, &status, 0);
	// return (handle_child_exit_status(status));
	return (true);
}

int	handler_heredoc(t_env_lst	*list)
{
	char	*delimiter;
	int		is_expand;

	printf("heredoc\n");
	delimiter = NULL;
	is_expand = 0;
	ft_clculate_heredoc(list);
	while (list)
	{
		if (list->type == HERE_DOCUMENT && list->next)// handler is not find delimite
		{
			list = list->next;// skip heredoc
			delimiter = find_delimiter(list, &is_expand);
			data_struc()->heredoc_fd = open_heredoc();
			if (data_struc()->heredoc_fd < 0)
				return (data_struc()->exit_status = 2, 0);
			handle_forked_process(delimiter, is_expand);
		}
		list = list->next;
	}
	return (true);
}
