/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:15:42 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/15 22:44:44 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_direct_path(char **args)
{
	DIR	*dir;

	if (access(args[0], F_OK) == 0)
	{
		if (access(args[0], X_OK) == 0)
		{
			dir = opendir(args[0]);
			if (dir != NULL)
			{
				closedir(dir);
				return (handle_directory_error(args));
			}
			execve(args[0], args, data_struc()->g_envp);
			perror(args[0]);
		}
		else if (opendir(args[0]) != NULL)
			return (handle_directory_error(args));
		else
			return (handle_permission_error(args));
	}
	else
		return (handle_no_file_error(args));
	return (1);
}

static void	exec_command_path(char *cmd_path, char **args, t_string *st_string)
{
	if (execve(cmd_path, args, st_string->g_envp) == -1)
	{
		if (!closedir(opendir(cmd_path)))
		{
			printf("%s: Is a directory\n", args[0]);
			ft_malloc(0, 0);
			exit(126);
		}
		else
		{
			printf("%s: %s\n", args[0], strerror(errno));
			ft_malloc(0, 0);
			exit(errno);
		}
	}
}

static int	handle_special_cases(char **args)
{
	if (!args[0] || args[0][0] == '\0')
	{
		ft_malloc(0, 0);
		exit(127);
	}
	if (args[0][0] == '.' && args[0][1] == '\0')
	{
		printf("minishell : %s: filename argument required\n", args[0]);
		printf("%s: usage: %s filename [arguments]\n", args[0], args[0]);
		ft_malloc(0, 0);
		exit(2);
	}
	return (0);
}

int	handle_path_cases(char **args)
{
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		return (handle_direct_path(args));
	}
	else if (args[0][0] == '.' && args[0][1] == '.')
	{
		printf("%s: command not found\n", args[0]);
		return (127);
	}
	return (0);
}

void	handle_command_path(char **args, t_string *st_string)
{
	char	*cmd_path;
	int		exit_code;

	if (handle_special_cases(args))
		return ;
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/')
		|| (args[0][0] == '.' && args[0][1] == '.'))
	{
		exit_code = handle_path_cases(args);
		ft_malloc(0, 0);
		exit(exit_code);
	}
	cmd_path = find_path(args[0], st_string->g_envp);
	if (!cmd_path)
	{
		exit_code = handle_cmd_not_found(args);
		ft_malloc(0, 0);
		exit(exit_code);
	}
	exec_command_path(cmd_path, args, st_string);
}
