/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:35:42 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/19 17:15:21 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_child_pipe(int **child_pipe, int *pipe_fd, int i, int cmd_count)
{
	if (i < cmd_count - 1)
		*child_pipe = pipe_fd;
	else
		*child_pipe = NULL;
}

static void	process_pipeline_commands(t_string *st_string,
		t_pipeline_data *data)
{
	int				i;
	t_process_args	proc_args;

	i = 0;
	proc_args = (t_process_args){st_string, &data->list, &data->prev_fd,
		data->pids, 0, data->cmd_count};
	if (data_struc()->is_spliter)
	{
		process_command(&proc_args);
		return ;
	}
	while (data->list && i < data->cmd_count)
	{
		proc_args.i = i++;
		process_command(&proc_args);
	}
}

void	execute_pipeline(t_string *st_string)
{
	t_pipeline_data	*data;

	if (!st_string->head)
		return ;
	data = init_pipeline_data(st_string);
	if (!data)
		return ;
	process_pipeline_commands(st_string, data);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	wait_for_children(data->pids, data->cmd_count);
}
