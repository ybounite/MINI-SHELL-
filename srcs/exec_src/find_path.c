/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:22:31 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/17 16:12:43 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	*check_path_permissions(char *full_path, char *cmd)
{
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
			return (full_path);
		else
		{
			printf("%s: Permission denied\n", cmd);
			return (NULL);
		}
	}
	return (NULL);
}

static char	*search_in_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*permission_result;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		permission_result = check_path_permissions(full_path, cmd);
		if (permission_result)
			return (permission_result);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*direct_path;

	(void)envp;
	direct_path = check_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	path_env = get_env_value("PATH", data_struc());
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path(cmd, paths));
}
