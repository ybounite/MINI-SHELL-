/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:32:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/08 19:37:22 by ybounite         ###   ########.fr       */
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

char *skip_qoutes(char *str)
{
	while (isquotes(*str))
	{
		(*str)++;
	}
	return (str);
}
char	*expand_heredoc(char *str)
{
	int 	i;
	int		original_i;
	char	*tmp;
	char	*var_value;

	(1) && (tmp = ft_strdup("")), (i = 0), (original_i = 0);
	while (str[i])
	{
		while (isquotes(str[i]))
			tmp = ft_strjoin_char(tmp, str[i++]);
		if (str[i] == '\0')
			break ;
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			tmp = ft_strjoin(tmp, "$$");
			i +=2;
		}
		else if (str[i] == DOLLAR)
		{
			var_value = get_variable_value(get_variable_name(str, &i));
			tmp = ft_strjoin(tmp, var_value);
			if (original_i == i)
			{
				tmp = ft_strjoin_char(tmp, '$');
				i++;
			}
		}
		else if (str[i])
			tmp = ft_strjoin_char(tmp, str[i++]);
	}
	return (tmp);
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
		return (perror("minishell: fork"), 1);
	else if (pid == 0)
	{
		// signal(SIGINT, sigint_handler);// handler signal 
		read_and_process_heredoc_input(delimiter, dolar);
		close(data_struc()->heredoc_fd);
		ft_malloc(false, 0);
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
			list->value = ft_strdup("<");
			list = list->next;// skip heredoc
			delimiter = find_delimiter(list, &is_expand);
			printf("this herdoc\n");
			data_struc()->heredoc_fd = open_heredoc();
			if (data_struc()->heredoc_fd < 0)
				return (data_struc()->exit_status = 2, 0);
			handle_forked_process(delimiter, is_expand);
			list->value = data_struc()->heredoc_file;
		}
		list = list->next;
	}
	return (true);
}
