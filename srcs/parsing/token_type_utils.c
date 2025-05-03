/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:44:19 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/03 15:58:20 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

en_status	get_token_type_from_char(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '<' || c == '>')
		return (REDIRECTION);
	else
		return (CMD);
		// else if (c == '$')
		// 	return (DOLLAR);
}
