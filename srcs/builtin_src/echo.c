/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:58 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/11 15:43:06 by ybounite         ###   ########.fr       */
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
			return (ft_strdup(st_string->g_envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	builtin_echo(t_env_lst *list)
{
	t_env_lst	*current;
	int			n_flag;

	if (!list)
		return ;
	current = list;
	n_flag = 0;
	if (current && ft_strcmp(current->value, "echo") == 0)
		current = current->next;
	while (current && is_n_flag(current->value))
	{
		n_flag = 1;
		current = current->next;
	}
	while (current && current->type != PIPE)
	{
		printf("%s", current->value);
		current = current->next;
		if (current && current->type != PIPE)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}
