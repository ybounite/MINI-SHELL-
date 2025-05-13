/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:33:50 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 09:11:28 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_dash(t_string *st_string)
{
	char	*path;

	path = get_oldpwd(st_string);
	if (!path)
		printf("cd: OLDPWD not set\n");
	else
		printf("%s\n", path);
	return (path);
}

static char	*handle_options(char **args, t_string *st_string)
{
	if (args[1][1] == '\0')
		return (handle_dash(st_string));
	else if (args[1][1] == '-' && args[1][2] == '\0')
		return (handle_home());
	else if (args[1][1] != '-')
	{
		printf("cd: %s: invalid option\n", args[1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		return (NULL);
	}
	else
		return (args[1]);
}

static char	*get_path(char **args, t_string *st_string)
{
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0'))
		return (handle_home());
	else if (ft_strcmp(args[1], "--") == 0)
	{
		if (!args[2])
			return (handle_home());
		else
			return (args[2]);
	}
	else if (args[1][0] == '-')
		return (handle_options(args, st_string));
	else
		return (args[1]);
}

bool	size_cd(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i > 2);
}

void	builtin_cd(char **args, t_string *st_string)
{
	char	*path;

	if (size_cd(args))
	{
		printf("minishell: cd: too many arguments\n");
		data_struc()->exit_status = 1;
		return ;
	}
	if (!args[1])
		path = handle_home();
	else if (args[1][0] == '~')
		path = ft_strjoin(getenv("HOME"), args[1]);
	else if (args[1][0] == '-')
		path = handle_dash(st_string);
	else
		path = get_path(args, st_string);
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		data_struc()->exit_status = 1;
		perror("cd");
	}
	else
		update_pwd_env(st_string);
}
