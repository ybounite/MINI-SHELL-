/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:35:37 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 19:19:54 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_input_redirection(char *filename)
{
	int	fd;

	if (!filename)
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
				token `newline'\n",
						2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	prepare_output_redirection(char **args, int *i, int *flags,
		char **filename)
{
	int	append;

	append = (ft_strcmp(args[*i], ">>") == 0);
	*filename = args[*i + 1];
	if (!*filename)
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
            token `newline'\n",
						2);
		return (-1);
	}
	if (append)
		*flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
	return (0);
}

int	handle_output_redirection(char **args, int *i)
{
	int		fd;
	int		flags;
	char	*filename;

	if (prepare_output_redirection(args, i, &flags, &filename) < 0)
		return (-1);
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 126;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("minishell: dup2 failed\n", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirections(char **args)
{
	int	i;
	int	j;

	1 && (i = 0), (j = 0);
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		{
			if (handle_output_redirection(args, &i) < 0)
				return (-1);
			i += 2;
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			if (handle_input_redirection(args[i + 1]) < 0)
				return (-1);
			i += 2;
		}
		else if (ft_strcmp(args[i], "<<") == 0)
			i += 2;
		else
			args[j++] = args[i++];
	}
	args[j] = NULL;
	return (0);
}
