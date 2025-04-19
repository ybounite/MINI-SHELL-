#include "../../includes/minishell.h"

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	// Don't search PATH for commands that contain /
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				ft_free_split(paths);
				return (full_path);
			}
			else
			{
				printf("%s: Permission denied\n", cmd);
				free(full_path);
				ft_free_split(paths);
				return (NULL);
			}
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

void	execute_builtin(char **args, t_string *st_string)
{
	if (!ft_strcmp(args[0], "echo"))
		builtin_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		builtin_cd(args, st_string);
	else if (!ft_strcmp(args[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(args[0], "export"))
		builtin_export(args, st_string);
	else if (!ft_strcmp(args[0], "unset"))
		builtin_unset(args, st_string);
	else if (!ft_strcmp(args[0], "env"))
		builtin_env(st_string);
	else if (!ft_strcmp(args[0], "exit"))
		builtin_exit(args);
}

static void	handle_child_process(char **args, int prev_fd, int *pipe_fd,
		t_string *st_string)
{
	char	*cmd_path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pipe_fd)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	// Execute the command
	if (is_builtin(args[0]))
	{
		execute_builtin(args, st_string);
		exit(0);
	}
	else
	{
		cmd_path = find_path(args[0], st_string->g_envp);
		if (!cmd_path)
		{
			if (args[0][0] == '/' || args[0][0] == '.')
			{
				if (access(args[0], X_OK) == 0)
				{
					execve(args[0], args, st_string->g_envp);
					perror("execve");
				}
			}
			printf("%s: command not found\n", args[0]);
			ft_free_split(args);
			exit(127);
		}
		execve(cmd_path, args, st_string->g_envp);
		free(cmd_path);
		perror("execve");
		ft_free_split(args);
		exit(1);
	}
}

static void	handle_parent_process(int *prev_fd, int *pipe_fd, pid_t pid)
{
	if (pipe_fd)
		close(pipe_fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd)
		*prev_fd = pipe_fd[0];
	else
		*prev_fd = -1;
	waitpid(pid, NULL, 0);
}

void	execute_pipeline(t_string *st_string)
{
	int			pipe_fd[2];
	int			prev_fd;
	pid_t		pid;
	char		**args;
	int			*child_pipe_fd;
	int			*parent_pipe_fd;
	t_env_lst	*list;

	prev_fd = -1;
	if (!st_string->head)
		return ;
	list = st_string->head;
	while (list)
	{
		args = git_array(&list);
		if (!args)
			break ;
		if (list && list->type == PIPE)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				ft_free_split(args);
				return ;
			}
			if (!list->next)
			{
				perror("minishell: parse error near `|'\n");
				break ;
			}
			list = list->next;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			ft_free_split(args);
			return ;
		}
		if (pid == 0)
		{
			child_pipe_fd = NULL;
			if (list) // If there are more commands after this one
				child_pipe_fd = pipe_fd;
			handle_child_process(args, prev_fd, child_pipe_fd, st_string);
		}
		else
		{
			parent_pipe_fd = NULL;
			if (list) // If there are more commands after this one
				parent_pipe_fd = pipe_fd;
			handle_parent_process(&prev_fd, parent_pipe_fd, pid);
			ft_free_split(args);
		}
	}
	if (prev_fd != -1)
		close(prev_fd);
}
