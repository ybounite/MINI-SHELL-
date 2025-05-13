/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:36:19 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 16:05:58 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(130);
}

void	hendle_sigquit(int signum)
{
	(void)signum;
	exit(131);
}

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pids[i], &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			{
				write(1, "\nQuit (core dumped)\n", 20);
				g_exit_status = 131;
			}
			else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				g_exit_status = 130;
			assign_signals_handler();
			if (i == cmd_count - 1 && WIFEXITED(status))
				update_exit_status(status);
		}
		i++;
	}
}

void	manage_child_process(t_string *st_string, int prev_fd, int *child_pipe,
		char **args)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, hendle_sigquit);
	handle_child_process(args, prev_fd, child_pipe, st_string);
}

void	handle_pipe_fds(int *pipe_fd, int *prev_fd, int i, int cmd_count)
{
	if (i < cmd_count - 1)
		close(pipe_fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < cmd_count - 1)
		*prev_fd = pipe_fd[0];
	else
		*prev_fd = -1;
}
