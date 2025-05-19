/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:33:03 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/19 11:21:21 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_and_not_found(char *new_value, char *key, char *equals_pos,
		t_string *st_string)
{
	char	*key_equals;
	char	*combined;

	st_string->found = 1;
	new_value = equals_pos + 1;
	key_equals = ft_strjoin(key, "=");
	combined = ft_strjoin(key_equals, new_value);
	add_new_entry(combined, st_string);
}

int	env_len(t_string *st_string)
{
	int	i;

	i = 0;
	while (st_string->g_envp[i])
		i++;
	return (i);
}

int	update_existing_entry(char *key, int key_len, char *entry,
		t_string *st_string)
{
	int	i;
	int	has_equals;

	has_equals = (entry[key_len] == '=');
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], key, key_len) == 0
			&& (st_string->g_envp[i][key_len] == '='
			|| st_string->g_envp[i][key_len] == '\0'))
		{
			if (has_equals || st_string->g_envp[i][key_len] == '=')
			{
				st_string->g_envp[i] = ft_strdup(entry);
				return (1);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_new_entry(char *entry, t_string *st_string)
{
	int		len;
	char	**new_env;
	int		i;

	len = env_len(st_string);
	new_env = ft_malloc(sizeof(char *) * (len + 2), 1);
	if (!new_env)
		return ;
	i = 0;
	while (i < len)
	{
		new_env[i] = st_string->g_envp[i];
		i++;
	}
	new_env[len] = entry;
	new_env[len + 1] = NULL;
	st_string->g_envp = new_env;
	data_struc()->g_envp = new_env;
}

void	builtin_export(char **args, t_string *st_string)
{
	int	i;

	if (!args[1])
	{
		print_export(st_string);
		return ;
	}
	i = 1;
	while (args[i])
	{
		add_or_update(args[i], st_string);
		i++;
	}
}
