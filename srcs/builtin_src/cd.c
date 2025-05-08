/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:33:50 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/08 09:38:53 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_oldpwd(t_string *st_string)
{
	int	i;

	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], "OLDPWD=", 7) == 0)
			return (st_string->g_envp[i] + 7);
		i++;
	}
	return (NULL);
}

static void	update_oldpwd(char *old_pwd, t_string *st_string)
{
	int	i;

	if (!old_pwd)
		return ;
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], "OLDPWD=", 7) == 0)
		{
			st_string->g_envp[i] = ft_strjoin("OLDPWD=", old_pwd);
			return ;
		}
		i++;
	}
}

static void	update_pwd(t_string *st_string)
{
	char	cwd[PATH_MAX];
	int		i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], "PWD=", 4) == 0)
		{
			st_string->g_envp[i] = ft_strjoin("PWD=", cwd);
			return ;
		}
		i++;
	}
}

static void	update_pwd_env(t_string *st_string)
{
	char	*old_pwd;
	int		i;

	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], "PWD=", 4) == 0)
		{
			old_pwd = ft_strdup(st_string->g_envp[i] + 4);
			update_pwd(st_string);
			update_oldpwd(old_pwd, st_string);
			return ;
		}
		i++;
	}
	update_pwd(st_string);
}

static char	*handle_home(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
		printf("cd: HOME not set\n");
	return (path);
}

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
	if (args[1][1] == '\0') // just "-"
		return (handle_dash(st_string));
	else if (args[1][1] == '-' && args[1][2] == '\0') // "--" alone
		return (handle_home());
	else if (args[1][1] != '-') // Any other option like "-a"
	{
		printf("cd: %s: invalid option\n", args[1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		return (NULL);
	}
	else // "--something" - treat it as a directory name
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
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i > 2);
}
void	builtin_cd(char **args, t_string *st_string)
{
	char	*path;
	
	if(size_cd(args))
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
