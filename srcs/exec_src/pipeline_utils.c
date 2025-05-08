#include "../../includes/minishell.h"

void	handle_parent_process(int *prev_fd, int *pipe_fd, pid_t pid,
		int *status)
{
	if (pipe_fd)
		close(pipe_fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd)
		*prev_fd = pipe_fd[0];
	else
		*prev_fd = -1;
	waitpid(pid, status, 0);
}

int	setup_pipe(int pipe_fd[2], t_env_lst *list)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	if (!list->next)
	{
		perror("minishell: parse error near `|'\n");
		return (0);
	}
	return (1);
}

int	create_process(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (0);
	}
	return (1);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		data_struc()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data_struc()->exit_status = 128 + WTERMSIG(status);
	else
		data_struc()->exit_status = 1;
}
