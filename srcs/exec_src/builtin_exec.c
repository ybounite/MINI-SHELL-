/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:19:31 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/08 14:33:42 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		builtin_echo(st_string->head);
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
		builtin_exit(args, st_string);
}
