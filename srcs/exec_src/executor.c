/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:25:32 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/18 20:26:30 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_cmd_not_found(char **args)
{
	if (args[0][0] == '/' || args[0][0] == '.')
		return (handle_direct_path(args));
	else
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
}

char	**env_list_to_array(char **args, t_env_lst *current)
{
	int	i;

	i = 0;
	args = ft_malloc(sizeof(char *) * (lstsize(current) + 1), true);
	while (current)
	{
		args[i++] = ft_strdup(current->value);
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

char	**git_array(t_env_lst **list)
{
	char		**args;
	t_env_lst	*current;

	int (i), (count);
	1 && (args = NULL), (count = 0), (i = 0), (current = *list);
	if (data_struc()->is_spliter)
		return (env_list_to_array(args, current));
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

	1 && (saved_stdin = -1), (saved_stdout = -1), status = 0;
	if (!st_string->head)
		return ;
	list = st_string->head;
	args = git_array(&list);
	if (!args || !args[0] || (args[0][0] == '\0' && data_struc()->is_empty == 1
		&& args[1] == NULL))
	{
		g_exit_status = 0;
		return ;
	}
	if (!has_pipe(st_string->head) && st_string->head->type == BUILTINS)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		handle_builtin_execution(args, st_string, saved_stdout, saved_stdin);
		return ;
	}
	execute_pipeline(st_string);
}
