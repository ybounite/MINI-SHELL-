/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:48:04 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/18 17:07:35 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else
		return (CMD);
	// else if (c == '*')
	// 	return (ASTERISK);
}

int	lenofwords_qoutes(char *str, int start, char qoute)
{
	int	len;

	len = 0;
	while (str[start] && str[start] != qoute)
	{
		len++;
		start++;
	}
	return (len);
}

void	handler_qoutes(t_env_lst **list, char *str, int *i,
		en_status_type state)
{
	char	qoutes;
	char	*ptr;
	int		index;

	index = 0;
	qoutes = str[(*i)++];
	ptr = malloc(lenofwords_qoutes(str, *i, qoutes) + 1);
	while (str[*i] && str[*i] != qoutes)
	{
		ptr[index++] = str[(*i)++];
	}
	(*i)++;
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}

int	lentword(char *str, int start)
{
	int	len;

	len = 0;
	while (str[start] && str[start] != SPACE)
	{
		start++;
		len++;
	}
	return (len);
}

void	handler_words(t_env_lst **list, char *str, int *i, en_status_type state)
{
	int		index;
	char	*ptr;
	int		len;

	index = 0;
	len = lentword(str, *i);
	if (len == 0)
		return ;
	ptr = malloc(lentword(str, *i) + 1);
	if (!ptr)
		return ;
	while (str[*i] && str[*i] != SPACE)
	{
		if (str[*i] == '\\')
			(*i)++;
		ptr[index++] = str[(*i)++];
	}
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}

void	handler_operator(t_env_lst **list, char *str, int *i,
		en_status_type state)
{
	int		index;
	char	*ptr;

	index = 0;
	ptr = malloc(3 * sizeof(char));
	if (!ptr)
		return ;
	while (str[*i] && str[*i] != SPACE)
		ptr[index++] = str[(*i)++];
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}

void	handler_parenthesis(t_env_lst **list, char *str, int *i,
		en_status_type state)
{
	int		index;
	char	charcter;
	char	*ptr;

	charcter = str[*i];
	index = 0;
	ptr = malloc(lentword(str, *i) + 1);
	while (str[*i] && str[*i] != ')')
		ptr[index++] = str[(*i)++];
	ptr[index++] = ')';
	ptr[index] = '\0';
	(*i)++;
	ft_add_newtoken(list, ptr, state);
}
// edite here
void	ft_spliter(t_env_lst **list, char *line)
{
	en_status_type	stats;
	int				i;

	i = 0;
	if (!line || !*line)
	{
		printf("ft_spliter: Empty line\n");
		return ;
	}
	while (line[i])
	{
		while (line[i] && line[i] == SPACE)
			i++;
		stats = find_type_state(line[i]);
		if (stats == CMD)
			handler_words(list, line, &i, stats);
		else if (stats == SINGLE_QUOTE || stats == DOUBLE_QUOTE)
			handler_qoutes(list, line, &i, stats);
		else if (stats == OR || stats == PIPE || stats == AND
			|| stats == REDIRECTION)
			handler_operator(list, line, &i, stats);
		else if (stats == PARENTHESIS)
			handler_parenthesis(list, line, &i, stats);
		if (!*list)
			printf("ft_spliter: No tokens added\n");
	}
}
