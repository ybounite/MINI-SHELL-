/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:33:57 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/06 14:34:09 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize(char **tokins, t_env_lst **list)
{
	int			i;
	en_status	stats;

	i = 0;	
	while (tokins[i])
	{
		stats =  get_token_type(tokins[i]);
		ft_add_newtoken(list, tokins[i], stats);
		i++;
	}
}

en_status	get_redirection_type_from_str(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (APPEND_REDIRECTION);
	else if (!ft_strcmp(str, "<<"))
		return (HERE_DOCUMENT);
	else if (!ft_strcmp(str, "<"))
		return (INPUT_REDIRECTION);
	else
		return (OUTPUT_REDIRECTION);
}

en_status	get_token_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND_REDIRECTION);
	else if (!ft_strcmp(str, "<<"))
		return (HERE_DOCUMENT);
	else if (!ft_strcmp(str, "<"))
		return (INPUT_REDIRECTION);
	else if (!ft_strcmp(str, ">"))
		return (OUTPUT_REDIRECTION);
	else if (!ft_strncmp(str, "'", 1))
		return (SINGLE_QUOTE);
	else if (!ft_strncmp(str, "\"", 1))
		return (DOUBLE_QUOTE);
	else if (is_builtin(str))
		return (BUILTINS);
	else
		return (CMD);
}
