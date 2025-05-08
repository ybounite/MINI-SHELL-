/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:58 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/08 11:09:57 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_extra_spaces(char *str)
{
	int	i = 0, j;
	int	space_found;

	i = 0, j = 0;
	space_found = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
		{
			str[j++] = str[i];
			space_found = 0;
		}
		else if (!space_found)
		{
			str[j++] = ' ';
			space_found = 1;
		}
		i++;
	}
	// Remove trailing space if any
	if (j > 0 && str[j - 1] == ' ')
		j--;
	str[j] = '\0';
}

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
	// Search environment variables
	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strncmp(st_string->g_envp[i], name, len) == 0
			&& st_string->g_envp[i][len] == '=')
		{
			// remove_extra_spaces(st_string->g_envp[i]);e
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
