/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:35:42 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/18 20:10:21 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_directory_error(char **args)
{
	printf("%s: Is a directory\n", args[0]);
	return (126);
}

static int	count_commands(t_env_lst *list)
{
	int	cmd_count;

	cmd_count = 1;
	while (list)
	{
		if (list->type == PIPE)
			cmd_count++;
		list = list->next;
	}
	return (cmd_count);
}

static void	initialize_pids(pid_t *pids, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		pids[i] = -1;
		i++;
	}
}

t_pipeline_data	*init_pipeline_data(t_string *st_string)
{
	t_pipeline_data	*data;

	data = ft_malloc(sizeof(t_pipeline_data), 1);
	if (!data)
		return (NULL);
	data->prev_fd = -1;
	data->cmd_count = count_commands(st_string->head);
	data->pids = ft_malloc(sizeof(pid_t) * data->cmd_count, 1);
	if (!data->pids)
		return (NULL);
	initialize_pids(data->pids, data->cmd_count);
	data->list = st_string->head;
	return (data);
}

void	process_command(t_process_args *args)
{
	char	**cmd_args;
	int		pipe_fd[2];
	int		*child_pipe;

	cmd_args = git_array(args->list);
	if (!cmd_args)
		return ;
	setup_command_pipe(pipe_fd, args->list, args->i, args->cmd_count);
	if (!create_process(&(args->pids[args->i])))
		return ;
	if (args->pids[args->i] == 0)
	{
		setup_child_pipe(&child_pipe, pipe_fd, args->i, args->cmd_count);
		manage_child_process(args->st_string, *(args->prev_fd), child_pipe,
			cmd_args);
	}
	handle_pipe_fds(pipe_fd, args->prev_fd, args->i, args->cmd_count);
}
