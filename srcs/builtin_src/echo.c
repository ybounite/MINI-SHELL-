/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:58 by bamezoua          #+#    #+#             */
/*   Updated: 2025/04/30 09:24:36 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

char	*get_env_value(char *var_name, t_string *st_string)
{
	int		i;
	int		len;
	char	*name;

	if (!var_name || !st_string || !st_string->g_envp)
		return (ft_strdup(""));
	if (var_name[0] == '$')
		name = var_name + 1;
	else
		name = var_name;
	len = ft_strlen(name);
	if (len == 0)
		return (ft_strdup(""));
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], name, len) == 0
			&& st_string->g_envp[i][len] == '=')
		{
			return (ft_strdup(st_string->g_envp[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	builtin_echo(char **args, t_string *st_string)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	(void)st_string;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
}
