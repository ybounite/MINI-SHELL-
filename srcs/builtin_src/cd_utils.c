/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:10:59 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 09:11:43 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_oldpwd(t_string *st_string)
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

void	update_oldpwd(char *old_pwd, t_string *st_string)
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

void	update_pwd(t_string *st_string)
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

void	update_pwd_env(t_string *st_string)
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

char	*handle_home(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
		printf("cd: HOME not set\n");
	return (path);
}
