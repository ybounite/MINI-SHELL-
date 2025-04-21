#include "../../includes/minishell.h"

static int	handle_input_redirection(char *filename)
{
	int	fd;

	if (!filename)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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

int	handle_output_redirection(char **args, int *i)
{
	int		fd;
	int		flags;
	int		append;
	char	*filename;

	append = (ft_strcmp(args[*i], ">>") == 0);
	filename = args[*i + 1];
	if (!filename)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (-1);
	}
	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
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

int handle_heredoc_redirection(char *delimiter)
{
    char    *line;
    int     pipe_fd[2];
    int     saved_stdin;

    if (!delimiter)
        return (0);
    saved_stdin = dup(STDIN_FILENO);
    if (saved_stdin == -1)
        return (0);
    if (pipe(pipe_fd) == -1)
    {
        close(saved_stdin);
        perror("pipe");
        return (0);
    }
    signal(SIGINT, SIG_DFL);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    assign_signals_handler();
    return (1);
}

int	redirections(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
		{
			if (handle_heredoc_redirection(args[i + 1]) == 0)
				return (-1);
			i += 2;
		}
		else
			args[j++] = args[i++];
	}
	args[j] = NULL;
	return (0);
}
