/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:31:43 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/01 19:01:01 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid_key(char *s)
{
	int i;

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

void unset_var(char *key, t_string *st_string)
{
	int len;
	char **new_env;
	int count;
	int i;
	int j;

	len = ft_strlen(key);
	count = 0;
	i = 0;
	while (st_string->g_envp[i])
	{
		if (!(!ft_strncmp(st_string->g_envp[i], key, len) && st_string->g_envp[i][len] == '='))
			count++;
		i++;
	}
	new_env = ft_malloc(sizeof(char *) * (count + 1), 1);
	if (!new_env)
		return;
	i = 0;
	j = 0;
	while (st_string->g_envp[i])
	{
		if (!(!ft_strncmp(st_string->g_envp[i], key, len) && st_string->g_envp[i][len] == '='))
			new_env[j++] = st_string->g_envp[i];
		i++;
	}
	new_env[j] = NULL;
	st_string->g_envp = new_env;
}

void builtin_unset(char **args, t_string *st_string)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			unset_var(args[i], st_string);
		i++;
	}
}
