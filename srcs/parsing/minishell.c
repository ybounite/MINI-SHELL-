/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:08 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 22:42:07 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_exit_status = 0;

char	**env_empty(void)
{
	char	**new_envp;

	new_envp = ft_malloc(sizeof(char *) * 4, 1);
	if (!new_envp)
		return (NULL);
	new_envp[0] = ft_strdup("PWD=/home/bamezoua/Desktop/MINI-SHELL-");
	new_envp[1] = ft_strdup("SHLVL=0");
	new_envp[2] = ft_strdup("_=/usr/bin/env");
	if (!new_envp[0])
		return (NULL);
	new_envp[3] = NULL;
	return (new_envp);
}

char	**duplicate_envp(char **envp)
{
	int		len;
	char	**new_envp;

	len = 0;
	while (envp[len])
		len++;
	if (len == 0)
	{
		new_envp = env_empty();
		data_struc()->g_envp = new_envp;
		return (new_envp);
	}
	new_envp = ft_malloc(sizeof(char *) * (len + 1), 1);
	if (!new_envp)
		return (NULL);
	len = 0;
	while (envp[len])
	{
		new_envp[len] = ft_strdup(envp[len]);
		if (!new_envp[len])
			return (NULL);
		len++;
	}
	new_envp[len] = NULL;
	return (new_envp);
}

void	handel_shlvl(t_string *st_string)
{
	char	*shlvl;
	int		shlvl_value;
	char	*new_shlvl;

	shlvl = get_env_value("SHLVL", st_string);
	if (shlvl)
	{
		shlvl_value = ft_atoi(shlvl) + 1;
		if (shlvl_value < 0)
			shlvl_value = 0;
		else if (shlvl_value > 1000)
			shlvl_value = 1;
		new_shlvl = ft_itoa(shlvl_value);
		if (new_shlvl)
		{
			shlvl = ft_strjoin("SHLVL=", new_shlvl);
			if (shlvl)
				add_or_update(shlvl, st_string);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_string	st_string;

	(void)argc;
	(void)argv;
	ft_bzero(&st_string, sizeof(st_string));
	st_string.g_envp = duplicate_envp(envp);
	data_struc()->g_envp = st_string.g_envp;
	handel_shlvl(&st_string);
	g_exit_status = 0;
	assign_signals_handler();
	start_shell_session(st_string);
	return (0);
}
