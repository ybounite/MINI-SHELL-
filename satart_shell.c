/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satart_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/09 19:52:55 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strhandler_quotes(char *ptr, char *str, int *i, int *index)
{
	char quots;

	if (i - 1 > 0 && find_space(str[(*i) - 1]))
				ptr[(*index)++] = SPACE;
	quots = str[*i];
	ptr[(*index)++] = str[(*i)++];
	while (str[*i] && str[*i] != quots)
		ptr[(*index)++] = str[(*i)++];
	ptr[(*index)++] = str[(*i)++];
}

void	strhandler_operator(char *ptr, char *str, int *i, int *index)
{
	char operator;

	ptr[(*index)++] = SPACE;
	operator = str[*i];
	while (str[*i] && str[*i] == operator)
		ptr[(*index)++] = str[(*i)++];
	if (str[*i] && !find_space(str[*i]))
		ptr[(*index)++] = SPACE;
}

void	handlerword(char *ptr, char *line, int *index, int *i)
{
	if (*i - 1 > 0 && find_space(line[*i - 1]))
		ptr[(*index)++] = SPACE;
	ptr[(*index)++] = line[(*i)++];
}

char	*handler_string(char *line)
{
	char	*ptr;
	int		index;
	int		i;
	int		size;

	i = 0;
	index = 0;
	size = ft_lenword(line);
	if (size < 0)
		return NULL;
	ptr = malloc(size + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	while (line[i])
	{
		ft_skip_whitespace(line, &i);
		if (line[i] && isquotes(line[i]))// handler quotes 
			strhandler_quotes(ptr, line, &i, &index);
		else if (line[i] && is_operator(line[i]))// handler operatoin
			strhandler_operator(ptr, line, &i, &index);
		else // handler word
			handlerword(ptr, line, &index, &i);
	}
	ptr[index] = '\0';
	return ptr;
}

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst *head;

	head = NULL;
	st_string->strcon = handler_string(st_string->line);
	// if ()// check if this error 
	if (!st_string->strcon)
		return (0);
	ft_spliter(&head, st_string->strcon);
	print_lst_tokens(head);
	return 1;
}

void	start_shell_session(t_string st_string)
{
	while (1)
	{
		st_string.line = get_line();
		handle_input_syntax(&st_string);
		free(st_string.line);
		st_string.line = NULL;
		// exectoction();
	}
}
