#include "../includes/minishell.h"

/* Update the exit status based on command result */
static void	update_exit_status(int status, int has_next_command)
{
    if (!has_next_command)
    {
        if (WIFEXITED(status))
            g_last_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_last_exit_status = 128 + WTERMSIG(status);
    }
}

/* Handle a single command in a pipeline */
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
	
	// Special handling for builtin cd - execute directly if it's the only command
	if (!has_next_command && *prev_fd == -1 && ft_strncmp(expanded_cmd, "cd", 2) == 0 
		&& (expanded_cmd[2] == ' ' || expanded_cmd[2] == '\0')) {
		if (!handle_redirections(expanded_cmd, &clean_cmd))
		{
			free(expanded_cmd);
			g_last_exit_status = 1;
			return;
		}
		handle_builtin(clean_cmd, envp);
		free(expanded_cmd);
		free(clean_cmd);
		return;
	}
	
	pid = fork();
	if (pid == 0)
	{
		// Setup pipes first
		setup_child_pipes(*prev_fd, pipe_fd, has_next_command);
		// Then handle redirections and clean command
		if (!handle_redirections(expanded_cmd, &clean_cmd))
		{
			free(expanded_cmd);
			exit(1);
		}
		free(expanded_cmd);
		// Execute the clean command
		if (ft_strlen(clean_cmd) > 0)
		{
			if (is_builtin(clean_cmd))
				handle_builtin(clean_cmd, envp);
			else
				execute_external(clean_cmd, envp);
		}
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
	update_exit_status(status, has_next_command);
}

/* Execute a command line with potential pipes */
void	execute_command(char *line, char **envp)
{
	char **commands;
	int pipe_fd[2];
	int prev_fd;
	int i;
	int has_next_command;

	commands = ft_split(line, '|');
	if (!commands || !commands[0])
		return ;
	prev_fd = -1;
	i = 0;
	while (commands[i])
	{
		has_next_command = (commands[i + 1] != NULL);
		if (has_next_command && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			break ;
		}
		handle_pipe_command(commands[i], &prev_fd, pipe_fd, envp,
			has_next_command);
		i++;
	}
	ft_free_split(commands);
}