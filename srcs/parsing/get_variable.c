/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:41:28 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/13 08:00:24 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_variable_name(const char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i + 1; // Skip '$'
	len = 0;
	if (!str[start])
		return (NULL);
	if (str[start] == '?')
	{
		*i += 2;
		return (ft_strdup("?"));
	}
	while (str[start + len] && (ft_isalnum(str[start + len]) || str[start
			+ len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	*i += len + 1;
	return (var_name);
}

char	*get_variable_value(char *var_name)
{
	char	*value;
	char	*exit_status_str;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_status_str = ft_itoa(data_struc()->exit_status);
		return (exit_status_str);
	}
	value = get_env_value(var_name, data_struc());
	if (!value)
	{
		data_struc()->exit_status = 0;
		return (ft_strdup(""));
	}
	return (ft_strdup(value));
}
