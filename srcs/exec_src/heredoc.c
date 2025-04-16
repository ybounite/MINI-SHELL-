#include "../../includes/minishell.h"

/*
** setup_heredoc: Handle heredoc redirection (<<)
** Returns: 1 on success, 0 on failure
*/
int	setup_heredoc(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];
	int		saved_stdin;

	if (!delimiter)
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	printf("> "); // Initial prompt
	while (1)
	{
		line = readline("");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		printf("> "); // Continue prompting
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (1);
}

/*
** reset_redirections: Reset file descriptors to their original state
*/
void	reset_redirections(int *saved_fds)
{
	if (saved_fds[0] != -1)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		close(saved_fds[0]);
	}
	if (saved_fds[1] != -1)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[1]);
	}
}

/*
** save_redirections: Save original file descriptors
*/
void	save_redirections(int *saved_fds)
{
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
}
