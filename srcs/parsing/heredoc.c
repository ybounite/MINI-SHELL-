/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:32:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/07 18:53:57 by ybounite         ###   ########.fr       */
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


char	*ft_expand(char *line)
{
	// char	*expand;
	if (*line == '"' && *(line + 1) == '$')
		return (expand_string(line));
	if (isquotes(*line == '$'))
		return (expand_string(line));
	return (line);
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
			printf("%s\n", str_expand);
			write(data_struc()->heredoc_fd, str_expand, ft_strlen(str_expand));
		}
		else
			write(data_struc()->heredoc_fd, line, ft_strlen(line));
		write(data_struc()->heredoc_fd, "\n", 1);
		free(line);
	}
	return (true);
}

int	handle_forked_process(char *delimiter, bool dolar)
{
	pid_t	pid;
	int		status;

	(void)delimiter;
	(void)dolar;
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
		if (list->type == HERE_DOCUMENT && list->next)// handler is not find delimite
		{
			list = list->next;// skip heredoc
			delimiter = find_delimiter(list, &is_expand);
			printf("this herdoc\n");
			data_struc()->heredoc_fd = open_heredoc();
			if (data_struc()->heredoc_fd < 0)
				return (data_struc()->exit_status = 2, 0);
			handle_forked_process(delimiter, is_expand);
			// free(delimiter);
		}
		list = list->next;
	}
	return (true);
}
