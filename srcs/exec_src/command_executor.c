#include "../../includes/minishell.h"

/* Execute a simple command without pipes */
void	execute_simple_command(char *cmd, char **envp)
{
    char	*expanded_cmd;
    char	*clean_cmd;
    int		saved_fds[2];
    int		should_exit;

    should_exit = 0;
    // Save original stdin/stdout
    save_redirections(saved_fds);
    // Expand environment variables
    expanded_cmd = expand_env_variables(cmd, envp);
    if (!expanded_cmd)
        return ;
    // Process redirections and get clean command
    if (!handle_redirections(expanded_cmd, &clean_cmd))
    {
        free(expanded_cmd);
        reset_redirections(saved_fds);
        g_last_exit_status = 1;
        return ;
    }
    // Execute the clean command (if it's not empty after redirection processing)
    if (clean_cmd && ft_strlen(clean_cmd) > 0)
    {
        // Execute builtins in the current process
        if (is_builtin(clean_cmd))
            should_exit = handle_builtin(clean_cmd, envp);
        else
            execute_external(clean_cmd, envp);
    }
    // Cleanup
    free(expanded_cmd);
    free(clean_cmd);
    reset_redirections(saved_fds);
    // Handle exit command if needed
    if (should_exit)
        exit(g_last_exit_status);
}

/* Execute an external command */
void	execute_external(char *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		// In child process
		args = ft_split(cmd, ' ');
		if (!args)
			exit(1);
		path = find_path(args[0], envp);
		if (!path)
		{
			printf("minishell: %s: command not found\n", args[0]);
			ft_free_split(args);
			exit(127);
		}
		if (execve(path, args, envp) == -1)
		{
			perror("execve");
			ft_free_split(args);
			free(path);
			exit(1);
		}
	}
	else
	{
		// In parent process
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_exit_status = 128 + WTERMSIG(status);
	}
}

/* Execute a single command */
void	execute_single_command(char *cmd, char **envp)
{
	char	*expanded_cmd;
	char	*clean_cmd;
	char	**args;
	char	*path;

	expanded_cmd = expand_env_variables(cmd, envp);
	if (!expanded_cmd)
		return ;
	if (!handle_redirections(expanded_cmd, &clean_cmd))
	{
		free(expanded_cmd);
		g_last_exit_status = 1;
		return ;
	}
	free(expanded_cmd);
	if (!clean_cmd || ft_strlen(clean_cmd) == 0)
	{
		free(clean_cmd);
		return ;
	}
	args = ft_split(clean_cmd, ' ');
	free(clean_cmd);
	if (!args)
		return ;
	if (is_builtin(args[0]))
	{
		handle_builtin(args[0], envp);
		ft_free_split(args);
		return ;
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", args[0]);
		ft_free_split(args);
		g_last_exit_status = 127;
		return ;
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		free(path);
		ft_free_split(args);
		exit(1);
	}
}
