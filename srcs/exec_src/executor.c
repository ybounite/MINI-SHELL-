/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:38:04 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/08 15:14:49 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**git_array(t_env_lst **list)
{
	char		**args;
	t_env_lst	*current;
	int			i;
	int			count;

	count = 0;
	current = *list;
	while (current && current->type != PIPE)
	{
		count++;
		current = current->next;
	}
	if (count == 0)
		return (NULL);
	args = ft_malloc(sizeof(char *) * (count + 1), 1);
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

static void	handle_builtin_execution(char **args, t_string *st_string,
		int saved_stdout, int saved_stdin)
{
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
}

void	execute_command(t_string *st_string)
{
	t_env_lst	*list;
	char		**args;
	int			saved_stdout;
	int			saved_stdin;
	int			status;

	saved_stdout = -1;
	saved_stdin = -1;
	status = 0;
	if (!st_string->head)
		return ;
	list = st_string->head;
	args = git_array(&list);
	print_lst_tokens(st_string->head);
	if (!args || !args[0])
		return ;
	if (!has_pipe(st_string->head) && st_string->head->type == BUILTINS)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		handle_builtin_execution(args, st_string, saved_stdout, saved_stdin);
		return ;
	}
	execute_pipeline(st_string);
}
