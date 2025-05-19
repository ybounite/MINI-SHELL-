/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:01:50 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/19 11:18:32 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_append_mode(char *arg, int *append_mode, int *key_len)
{
	char	*key;
	char	*equals_pos;
	char	*temp;
	char	*plus_pos;

	equals_pos = ft_strchr(arg, '=');
	if (equals_pos && equals_pos > arg && *(equals_pos - 1) == '+')
	{
		*append_mode = 1;
		temp = ft_strdup(arg);
		plus_pos = ft_strchr(temp, '+');
		if (plus_pos)
			ft_memmove(plus_pos, plus_pos + 1, ft_strlen(plus_pos));
		key = extract_key(temp, key_len);
	}
	else
	{
		*append_mode = 0;
		key = extract_key(arg, key_len);
	}
	return (key);
}

static int	validate_key(char *key, char *arg)
{
	if (!key)
		return (0);
	if (!is_valid_key(key))
	{
		printf("export: `%s`: not a valid identifier\n", arg);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

static void	append_value(char *key, int key_len, char *equals_pos,
		t_string *st_string)
{
	int		i;
	char	*existing_value;
	char	*new_value;
	char	*combined;
	char	*key_equals;

	i = 0;
	st_string->found = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], key, key_len) == 0
			&& st_string->g_envp[i][key_len] == '=')
		{
			existing_value = st_string->g_envp[i] + key_len + 1;
			new_value = equals_pos + 1;
			combined = ft_strjoin(existing_value, new_value);
			key_equals = ft_strjoin(key, "=");
			st_string->g_envp[i] = ft_strjoin(key_equals, combined);
			st_string->found = 1;
			break ;
		}
		i++;
	}
	if (!st_string->found)
		append_and_not_found(new_value, key, equals_pos, st_string);
}

static char	*create_clean_entry(char *arg, int append_mode)
{
	char	*clean_arg;
	char	*plus_char;
	char	*entry;

	if (append_mode)
	{
		clean_arg = ft_strdup(arg);
		plus_char = ft_strchr(clean_arg, '+');
		if (plus_char)
			ft_memmove(plus_char, plus_char + 1, ft_strlen(plus_char));
		entry = ft_strdup(clean_arg);
	}
	else
		entry = ft_strdup(arg);
	return (entry);
}

void	add_or_update(char *arg, t_string *st_string)
{
	int		key_len;
	int		append_mode;
	char	*key;
	char	*equals_pos;
	char	*entry;

	key = handle_append_mode(arg, &append_mode, &key_len);
	if (!validate_key(key, arg))
		return ;
	equals_pos = ft_strchr(arg, '=');
	if (append_mode && equals_pos)
	{
		append_value(key, key_len, equals_pos, st_string);
		if (ft_strchr(st_string->g_envp[0], '='))
			return ;
	}
	entry = create_clean_entry(arg, append_mode);
	if (!entry)
		return ;
	if (!update_existing_entry(key, key_len, entry, st_string))
		add_new_entry(entry, st_string);
}
