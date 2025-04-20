#include "../../includes/minishell.h"

int	lstsize(t_env_lst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	**git_array(t_env_lst **list)
{
	char		**args;
	t_env_lst	*current;

	int i, count = 0;
	current = *list;
	if (current->type == PIPE)
		return (perror("minishell: parse error near `|'\n"), NULL);
	while (current && current->type != PIPE)
	{
		count++;
		current = current->next;
	}
	if (count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*list && (*list)->type != PIPE)
	{
		args[i++] = ft_strdup((*list)->value);
		*list = (*list)->next;
	}
	args[i] = NULL;
	return (args);
}

void	execute_command(t_string *st_string)
{
	t_env_lst	*list;
	char		**args;
	int			saved_stdout;
	int			saved_stdin;

	saved_stdout = -1;
	saved_stdin = -1;
	if (!st_string->head)
		return ;
	list = st_string->head;
	args = git_array(&list);
	if (!args || !args[0])
	{
		if (args)
			ft_free_split(args);
		return ;
	}
	if (!has_pipe(st_string->head))
	{
		if (is_builtin(args[0]))
		{
			saved_stdout = dup(STDOUT_FILENO);
			saved_stdin = dup(STDIN_FILENO);
			if (redirections(args) >= 0)
				execute_builtin(args, st_string);
			if (saved_stdout != -1)
			{
				dup2(saved_stdout, STDOUT_FILENO);
				close(saved_stdout);
			}
			if (saved_stdin != -1)
			{
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
			}
			ft_free_split(args);
			return ;
		}
	}
	ft_free_split(args);
	execute_pipeline(st_string);
}

int	has_pipe(t_env_lst *list)
{
	t_env_lst	*current;

	current = list;
	while (current)
	{
		if (current->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}
