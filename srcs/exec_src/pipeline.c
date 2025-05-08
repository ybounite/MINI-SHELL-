#include "../../includes/minishell.h"

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

static void	setup_child_pipe(int **child_pipe, int *pipe_fd, int i,
		int cmd_count)
{
	if (i < cmd_count - 1)
		*child_pipe = pipe_fd;
	else
		*child_pipe = NULL;
}

static void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (i == cmd_count - 1)
				update_exit_status(status);
		}
		i++;
	}
}

static void	process_command(t_string *st_string, t_env_lst **list, int *prev_fd,
		pid_t *pids, int i, int cmd_count)
{
	char	**args;
	int		pipe_fd[2];
	int		*child_pipe;

	args = git_array(list);
	if (!args)
		return ;
	if (i < cmd_count - 1 && *list && (*list)->type == PIPE)
	{
		if (!setup_pipe(pipe_fd, *list))
			return ;
		*list = (*list)->next;
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	if (!create_process(&pids[i]))
		return ;
	if (pids[i] == 0)
	{
		setup_child_pipe(&child_pipe, pipe_fd, i, cmd_count);
		handle_child_process(args, *prev_fd, child_pipe, st_string);
	}
	if (i < cmd_count - 1)
		close(pipe_fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < cmd_count - 1)
		*prev_fd = pipe_fd[0];
	else
		*prev_fd = -1;
}

void	execute_pipeline(t_string *st_string)
{
	int prev_fd;
	t_env_lst *list;
	pid_t *pids;
	int cmd_count;
	int i;

	prev_fd = -1;
	if (!st_string->head)
		return ;
	cmd_count = count_commands(st_string->head);
	pids = ft_malloc(sizeof(pid_t) * cmd_count, 1);
	if (!pids)
		return ;
	initialize_pids(pids, cmd_count);
	i = 0;
	list = st_string->head;
	while (list && i < cmd_count)
	{
		process_command(st_string, &list, &prev_fd, pids, i, cmd_count);
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_children(pids, cmd_count);
}
