#include "../includes/minishell.h"

static void	execute_child(char *command, char **envp)
{
	execute_single_command(command, envp);
	exit(1);
}

static void	handle_pipe_command(char *cmd, int *prev_fd, int *pipe_fd,
		char **envp, int has_next_command)
{
	pid_t	pid;
	char	*expanded_cmd;
	char	*clean_cmd;
	int		status;

	expanded_cmd = expand_env_variables(cmd, envp);
	if (!expanded_cmd)
		return ;
	pid = fork();
	if (pid == 0)
	{
		// Setup pipes first
		setup_child_pipes(*prev_fd, pipe_fd, has_next_command);
		// Then handle redirections
		if (!handle_redirections(expanded_cmd, &clean_cmd))
		{
			free(expanded_cmd);
			exit(1);
		}
		free(expanded_cmd);
		if (is_builtin(clean_cmd))
			handle_builtin(clean_cmd, envp);
		else
			execute_child(clean_cmd, envp);
		free(clean_cmd);
		exit(0);
	}
	free(expanded_cmd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next_command)
		close(pipe_fd[1]);
	*prev_fd = has_next_command ? pipe_fd[0] : -1;
	waitpid(pid, &status, 0);
	// Only update exit status for the last command in a pipeline
	if (!has_next_command)
	{
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_exit_status = 128 + WTERMSIG(status);
	}
}
