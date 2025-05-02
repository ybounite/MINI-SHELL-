/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:33:03 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/02 15:11:52 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int env_len(t_string *st_string)
{
	int i;

	i = 0;
	while (st_string->g_envp[i])
		i++;
	return (i);
}

static void sort_env(char **env)
{
	char *tmp;
	size_t len_i;
	size_t len_j;
	int i;
	int j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			len_i = ft_strlen(env[i]);
			len_j = ft_strlen(env[j]);
			if (len_i > len_j)
			{
				if (ft_strncmp(env[i], env[j], len_j) > 0)
				{
					tmp = env[i];
					env[i] = env[j];
					env[j] = tmp;
				}
			}
			else
			{
				if (ft_strncmp(env[i], env[j], len_i) > 0)
				{
					tmp = env[i];
					env[i] = env[j];
					env[j] = tmp;
				}
			}
			j++;
		}
		i++;
	}
}

static char **create_env_copy(t_string *st_string)
{
	char **copy;
	int i;
	int size;

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

static void print_env_entry(char *entry)
{
	char *sep;

	sep = ft_strchr(entry, '=');
	if (sep)
		printf("declare -x %.*s=\"%s\"\n", (int)(sep - entry), entry, sep + 1);
	else
		printf("declare -x %s\n", entry);
}

static void print_export(t_string *st_string)
{
	char **copy;
	int i;

	copy = create_env_copy(st_string);
	if (!copy)
		return;
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		print_env_entry(copy[i]);
		i++;
	}
}

static char *extract_key(char *arg, int *key_len)
{
	*key_len = 0;
	while (arg[*key_len] && arg[*key_len] != '=')
		(*key_len)++;
	return (ft_substr(arg, 0, *key_len));
}

static char *create_entry(char *arg, int key_len)
{
	char *value;

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

static int update_existing_entry(char *key, int key_len, char *entry,
								 t_string *st_string)
{
	int i;
	int has_equals;

	has_equals = (entry[key_len] == '=');
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], key, key_len) == 0 &&
			(st_string->g_envp[i][key_len] == '=' ||
			 st_string->g_envp[i][key_len] == '\0'))
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

static void add_new_entry(char *entry, t_string *st_string)
{
	int len;
	char **new_env;
	int i;

	len = env_len(st_string);
	new_env = ft_malloc(sizeof(char *) * (len + 2), 1);
	if (!new_env)
		return;
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

static void add_or_update(char *arg, t_string *st_string)
{
	int key_len;
	char *key;
	char *entry;
	char *equals_pos;
	int append_mode;

	append_mode = 0;
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos && equals_pos > arg && *(equals_pos - 1) == '+')
	{
		append_mode = 1;
		char *temp = ft_strdup(arg);
		char *plus_pos = ft_strchr(temp, '+');
		if (plus_pos)
			ft_memmove(plus_pos, plus_pos + 1, ft_strlen(plus_pos));
		key = extract_key(temp, &key_len);
	}
	else
		key = extract_key(arg, &key_len);
	if (!key)
		return;
	if (!is_valid_key(key))
	{
		printf("export: `%s`: not a valid identifier\n", arg);
		data_struc()->exit_status = 1;
		return;
	}
	if (append_mode)
	{
		char *existing_value = NULL;
		char *new_value = NULL;
		int i = 0;
		while (st_string->g_envp[i])
		{
			if (ft_strncmp(st_string->g_envp[i], key, key_len) == 0 &&
				st_string->g_envp[i][key_len] == '=')
			{
				existing_value = st_string->g_envp[i] + key_len + 1;
				new_value = equals_pos + 1;
				char *combined = ft_strjoin(existing_value, new_value);
				char *key_equals = ft_strjoin(key, "=");
				entry = ft_strjoin(key_equals, combined);
				st_string->g_envp[i] = entry;
				return;
			}
			i++;
		}
		char *clean_arg = ft_strdup(arg);
		char *plus_char = ft_strchr(clean_arg, '+');
		if (plus_char)
			ft_memmove(plus_char, plus_char + 1, ft_strlen(plus_char));

		entry = ft_strdup(clean_arg);
	}
	else
		entry = create_entry(arg, key_len);
	if (!entry)
		return;
	if (!append_mode && !update_existing_entry(key, key_len, entry, st_string))
		add_new_entry(entry, st_string);
	else if (append_mode && !update_existing_entry(key, key_len, entry, st_string))
		add_new_entry(entry, st_string);
}

void builtin_export(char **args, t_string *st_string)
{
	int i;

	if (!args[1])
	{
		print_export(st_string);
		return;
	}
	i = 1;
	while (args[i])
	{
		add_or_update(args[i], st_string);
		i++;
	}
}
