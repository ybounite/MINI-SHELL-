/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spilter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:53:14 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/07 19:22:42 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_space(char c)
{
	return (c == SPACE || c == TAB || c == NEWLINE);
}

bool	isoperator(char c)
{
	return (c == '>' || c == '<' || c == '|'
		|| c == '&' || c == '(' || c == ')');
}

bool	same_string(char *str, int *index, char c)//
{
	int i;

	i = *index;
	if (c == SPACE)
	{
		if (str[i] && !find_space(str[i]) && isoperator(str[i]) == 0)
			return (0);
		return(1);
	}
	else if ( str[i] == c)
		i++;
	if (str[i] && !find_space(str[i]) && isoperator(str[i]) == 0)
		return (0);
	return (1);
}

void	ft_skip_whitespace(char *str, int *index)
{
	while (str[*index] && find_space(str[*index]))
		(*index)++;
}

en_status_type	find_type_state(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '&')
		return (AND);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '<' || c == '>')
		return (REDIRECTION);
	else if (c == '(' || c == ')')
		return (PARENTHESIS);
	else if (c == '*')
		return (ASTERISK);
	else
		return (CMD);
}

void	add_lst_token(t_env_lst **head, char *token, en_status_type type, bool cat)
{
	t_env_lst	*new;
	new = creatnew_node(token, type, cat);
	if (!new)
		return ;
	lstadd_back(head, new);
}

void	handler_words(t_env_lst **head, char *str, int *index)
{
	char *token;
	int start;

	start = *index;
	ft_skip_whitespace(str, index);
	if (!str[*index])
		return ;
	while (str[*index] && !find_space(str[*index])
		&& find_type_state(str[*index]) == CMD)
		(*index)++;
	token = ft_substr(str, start, *index - start);
	add_lst_token(head, token, CMD, same_string(str, index, ' '));
}
