#include "../../includes/minishell.h"

/*
** setup_input_redirect: Handle input redirection (<)
** Returns: 1 on success, 0 on failure
*/
int	setup_input_redirect(char *file)
{
	int	fd;

	if (!file)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

/*
** setup_output_redirect: Handle output redirection (>)
*/
int	setup_output_redirect(char *file)
{
	int	fd;

	if (!file)
		return (0);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: Permission denied\n", file);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

/*
** setup_append_redirect: Handle append redirection (>>)
*/
int	setup_append_redirect(char *file)
{
	int	fd;

	if (!file)
		return (0);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: Permission denied\n", file);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

/*
** apply_redirections: Apply specified redirection
*/
int	apply_redirections(char *type, char *file)
{
	if (!type || !file)
		return (0);
	if (ft_strcmp(type, "<") == 0)
		return (setup_input_redirect(file));
	else if (ft_strcmp(type, ">") == 0)
		return (setup_output_redirect(file));
	else if (ft_strcmp(type, ">>") == 0)
		return (setup_append_redirect(file));
	else if (ft_strcmp(type, "<<") == 0)
		return (setup_heredoc(file));
	return (0);
}
