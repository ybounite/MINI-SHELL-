/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:51:58 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 09:52:01 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_env_copy(t_string *st_string)
{
	char	**copy;
	int		i;
	int		size;

	size = env_len(st_string);
	copy = ft_malloc(sizeof(char *) * (size + 1), 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(st_string->g_envp[i]);
		i++;
	}
	copy[i] = NULL;
	data_struc()->g_envp = copy;
	return (copy);
}

void	print_env_entry(char *entry)
{
	char	*sep;

	sep = ft_strchr(entry, '=');
	if (sep)
		printf("declare -x %.*s=\"%s\"\n", (int)(sep - entry), entry, sep + 1);
	else
		printf("declare -x %s\n", entry);
}

void	print_export(t_string *st_string)
{
	char	**copy;
	int		i;

	copy = create_env_copy(st_string);
	if (!copy)
		return ;
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		print_env_entry(copy[i]);
		i++;
	}
}

char	*extract_key(char *arg, int *key_len)
{
	*key_len = 0;
	while (arg[*key_len] && arg[*key_len] != '=')
		(*key_len)++;
	return (ft_substr(arg, 0, *key_len));
}

char	*create_entry(char *arg, int key_len)
{
	char	*value;

	if (arg[key_len] == '\0')
		return (ft_strdup(arg));
	else if (arg[key_len] == '=')
	{
		if (arg[key_len + 1] == '\0')
			return (ft_strdup(arg));
		value = arg + key_len + 1;
	}
	return (ft_strdup(arg));
}
