/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:30:26 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 09:17:57 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_dollar_expansion(char *str, int *i, char *tmp)
{
	int		original_i;
	char	*var_value;

	original_i = *i;
	if (ft_isdigit(str[*i + 1]))
		*i += 2;
	else if (str[*i + 1] == '$')
	{
		tmp = ft_strjoin(tmp, "$$");
		*i += 2;
	}
	else
	{
		var_value = get_variable_value(get_variable_name(str, i));
		tmp = ft_strjoin(tmp, var_value);
		if (original_i == *i)
		{
			tmp = ft_strjoin_char(tmp, '$');
			(*i)++;
		}
	}
	return (tmp);
}

static char	*process_expansion(char *str, int *i, char *tmp)
{
	while (isquotes(str[*i]))
		tmp = ft_strjoin_char(tmp, str[(*i)++]);
	if (str[*i] == '\0')
		return (tmp);
	if (str[*i] == DOLLAR)
		tmp = handle_dollar_expansion(str, i, tmp);
	else if (str[*i])
		tmp = ft_strjoin_char(tmp, str[(*i)++]);
	return (tmp);
}

char	*expand_heredoc(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		tmp = process_expansion(str, &i, tmp);
	}
	return (tmp);
}
