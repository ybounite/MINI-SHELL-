/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:36:25 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/01 19:05:28 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_redirections(int prev_fd, int *pipe_fd)
{
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
}

// static int	handle_env_variable_cmd(char **args, t_string *st_string)
// {
// 	char	*env_value;

// 	if (args[0] && args[0][0] == '$')
// 	{
// 		env_value = get_env_value(args[0], st_string);
// 		if (!env_value || env_value[0] == '\0')
// 		{
// 			if (env_value)
// 				free(env_value);
// 			ft_free_split(args);
// 			return (127);
// 		}
// 		free(args[0]);
// 		args[0] = env_value;
// 	}
// 	return (0);
// }

static void	exec_builtin_and_exit(char **args, t_string *st_string)
{
	execute_builtin(args, st_string);
	exit(0);
}

static int	handle_cmd_not_found(char **args)
{
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
			{
				execve(args[0], args, NULL);
				perror(args[0]);
			}
			else if (opendir(args[0]) != NULL)
			{
				printf("%s: Is a directory\n", args[0]);
				return (126);
			}
			else
			{
				printf("%s: Permission denied\n", args[0]);
				return (126);
			}
		}
		else
		{
			printf("%s: No such file or directory\n", args[0]);
			return (127);
		}
	}
	else
	{
		printf("%s: command not found\n", args[0]);
		return (127);
	}
	return (1);
}

static void	handle_command_path(char **args, t_string *st_string)
{
	char	*cmd_path;
	int		exit_code;

	if (!args[0] || args[0][0] == '\0')
	{
		// ft_free_split(args);
		exit(127);
	}
	cmd_path = find_path(args[0], st_string->g_envp);
	if (!cmd_path)
	{
		exit_code = handle_cmd_not_found(args);
		// ft_free_split(args);
		exit(exit_code);
	}
	if (execve(cmd_path, args, st_string->g_envp) == -1)
	{
		if (!closedir(opendir(cmd_path)))
		{
			printf("%s: Is a directory\n", args[0]);
			// free(cmd_path);
			// ft_free_split(args);
			exit(126);
		}
		else
		{
			printf("%s: %s\n", args[0], strerror(errno));
			// free(cmd_path);
			// ft_free_split(args);
			exit(errno);
		}
	}
}

void	handle_child_process(char **args, int prev_fd, int *pipe_fd,
		t_string *st_string)
{
	// int	ret;

	setup_redirections(prev_fd, pipe_fd);
	if (redirections(args) < 0)
		exit(1);
	// ret = handle_env_variable_cmd(args, st_string);
	// if (ret != 0)
	// 	exit(ret);
	if (is_builtin(args[0]))
		exec_builtin_and_exit(args, st_string);
	else
		handle_command_path(args, st_string);
}
