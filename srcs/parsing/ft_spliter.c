/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:48:04 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/24 21:08:13 by ybounite         ###   ########.fr       */
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
	else if (c == '$')
		return (DOLLAR);
	else
		return (CMD);
}

int	lenofwords_qoutes(char *str, int start)
{
	int		len;
	char	qoutes;
	len = 0;
	while (str[start] && str[start] != SPACE)
	{
		if (isquotes(str[start]))
		{
			qoutes = str[start++];
			while (str[start] && str[start] != qoutes)
			{
				start++;
				len++;
			}
			start++;// skip qoute 
		}
		else{
			while (str[start] && !isquotes(str[start]) && str[start] != SPACE)
			{
				start++;
				len++;	
			}
		}
		break;
	}
	return (len);
}
char	*ft_substring(char *str, int start , int len)
{
	int		i;
	char 	*ptr;
	i = 0;
	ptr = malloc(len + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	while (str[start] && i < len)
	{
		if (!isquotes(str[start]))
			ptr[i++] = str[start];
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
void	handler_qoutes(t_env_lst **list, char *str, int *i,
		en_status_type state)
{
	char	*ptr;
	int		index;
	int		len;

	(1) && (index = 0), (len = lenofwords_qoutes(str, *i));
	if (len == 0)
	{
		ft_add_newtoken(list, ft_strdup("\"\""), state);
		(*i) += 2;
		return ;
	}
	if (str[*i] == DOUBLE_QUOTE && str[*i + 1] == DOLLAR)
	{
		index = *i;
		heandler_dollar(list, str, &index, DOLLAR);
		*i = index;
		return ;
	}
	ptr = malloc(len + 1 * sizeof(char));
	if (!ptr)
		return ;
	while (str[*i] && index <= len)
	{
		if (!isquotes(str[*i]))
			ptr[index++] = str[*i];
		(*i)++;
	}
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}

int	lentword(char *str, int start)
{
	int		len;
	char	qouts;

	(1) && (len = 0), (qouts = 0);
	while (str[start] && str[start] != SPACE)
	{
		if (isquotes(str[start]))
		{
			qouts = str[start++];
			while (str[start] && str[start] != qouts)
			{
				start++;
				len++;
			}
			start++;
		}
		else
		{
			start++;
			len++;
		}
	}
	return (len);
}

int	lendollar(char *str, int start)
{
	int len;

	len = 0;
	if (str[start] == '?')
		return (1);
	while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))// $""
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
	char	qouts;
	(1) && (index = 0), (len = lentword(str, *i));
	if (len == 0)
		return ;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return ;
	while (str[*i] && str[*i] != SPACE)
	{
		if (isquotes(str[*i]))
		{
			qouts = str[(*i)++];
			while (str[*i] && str[*i] != qouts)
				ptr[index++] = str[(*i)++];
			(*i)++;// skip qouts 
		}
		else
			ptr[index++] = str[(*i)++];
	}
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}

en_status_type	find_states(char *str)
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
	if (state == REDIRECTION)
		state = find_states(ptr);
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

void	heandler_dollar(t_env_lst **list, char *str, int *i,
		en_status_type state)
{
	char	*ptr;
	int		index;
	int		len;

	index = 0;
	len = lendollar(str, ++(*i));
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return ;
	while (index < len && str[*i])
		ptr[index++] = str[(*i)++];
	ptr[index] = '\0';
	ft_add_newtoken(list, ptr, state);
}
// edite here
void	ft_spliter(t_env_lst **list, char *line)
{
	en_status_type stats;
	int i;

	i = 0;
	if (!line)
		return ;
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
		else if (stats == DOLLAR)
			heandler_dollar(list, line, &i, stats);
	}
}
