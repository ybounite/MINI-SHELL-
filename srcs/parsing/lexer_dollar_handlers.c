/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:23:31 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/29 09:47:07 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lendollar(char *str, int start)
{
	int len;

	len = 0;
	if (str[start] == '?')
		return (++len);
	while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))// $""
	{
		start++;
		len++;
	}
	return (len);
}
char *handler_expasion(char *var_name)
{
    int     i;
    int     len;
    char    *exit_status_str;

    if (!var_name || !data_struc()->g_envp)
        return (ft_strdup(""));
    if (var_name[0] == '$')
        var_name++;
    if (ft_strcmp(var_name, "?") == 0)
    {
        exit_status_str = ft_itoa(data_struc()->exit_status);
        return (exit_status_str);
    }
    len = ft_strlen(var_name);
    if (len == 0)
        return (ft_strdup(""));
    i = 0;
    while (data_struc()->g_envp[i])
    {
        if (ft_strncmp(data_struc()->g_envp[i], var_name, len) == 0
            && data_struc()->g_envp[i][len] == '=')
        {
            return (ft_strdup(data_struc()->g_envp[i] + len + 1));
        }
        i++;
    }
    return (ft_strdup(""));
}

void	heandler_dollar(t_env_lst **list, char *str, int *i, en_status state)
{
	char	*ptr;
	int		index;
	int		len;

	(index = 0), ((*i)++);
	if (isquotes(str[*i]))
		(*i)++;
	len = lendollar(str, *i);
	if (len < 0)
		return ;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return ;
	while (index < len && str[*i])
		ptr[index++] = str[(*i)++];
	ptr[index] = '\0';
	if (isquotes(str[*i]))
		(*i)++;
	ft_add_newtoken(list, handler_expasion(ptr), state);
	free(ptr);
}
