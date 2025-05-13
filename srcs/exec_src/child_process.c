/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:36:25 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 19:05:16 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_permission_error(char **args)
{
	printf("%s: Permission denied\n", args[0]);
	return (126);
}

int	handle_no_file_error(char **args)
{
	printf("%s: No such file or directory\n", args[0]);
	return (127);
}

void	setup_redirections(int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(1);
	}
	if (pipe_fd && pipe_fd[1] != -1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fd[0]);
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (pipe_fd && pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

static void	exec_builtin_and_exit(char **args, t_string *st_string)
{
	execute_builtin(args, st_string);
	ft_malloc(0, 0);
	exit(0);
}

void	handle_child_process(char **args, int prev_fd, int *pipe_fd,
		t_string *st_string)
{
	int	redir_result;

	setup_redirections(prev_fd, pipe_fd);
	if (!args || !args[0] || args[0][0] == '\0')
    {
        ft_putstr_fd("command not found\n", 2);
        ft_malloc(0, 0);
        exit(127);
    }
	redir_result = redirections(args);
	if (redir_result < 0)
	{
		ft_malloc(0, 0);
		exit(1);
	}
	if (is_builtin(args[0]))
		exec_builtin_and_exit(args, st_string);
	else
		handle_command_path(args, st_string);
}
