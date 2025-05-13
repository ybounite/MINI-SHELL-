/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:31:43 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 14:54:18 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_key(char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_env_var(char **envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_env_var(t_string *st_string, int index)
{
	int		i;
	int		env_count;
	char	**new_env;

	env_count = 0;
	while (st_string->g_envp[env_count])
		env_count++;
	new_env = ft_malloc(sizeof(char *) * env_count, 1);
	i = 0;
	env_count = 0;
	while (st_string->g_envp[i])
	{
		if (i != index)
			new_env[env_count++] = st_string->g_envp[i];
		i++;
	}
	new_env[env_count] = NULL;
	st_string->g_envp = new_env;
	data_struc()->g_envp = new_env;
}

void	builtin_unset(char **args, t_string *st_string)
{
	int	i;
	int	var_index;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			printf("unset: `%s': not a valid identifier\n", args[i]);
			g_exit_status = 1;
		}
		else
		{
			var_index = find_env_var(st_string->g_envp, args[i]);
			if (var_index >= 0)
				remove_env_var(st_string, var_index);
		}
		i++;
	}
}
