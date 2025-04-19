/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:46:25 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/19 13:07:02 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	strhandler_quotes(char *ptr, char *str, int *i, int *index)
{
	char	quots;

	if (i - 1 > 0 && find_space(str[(*i) - 1]))
		ptr[(*index)++] = SPACE;
	quots = str[*i];
	ptr[(*index)++] = str[(*i)++];
	while (str[*i] && str[*i] != quots)
		ptr[(*index)++] = str[(*i)++];
	ptr[(*index)++] = str[(*i)++];
}
// edite here
void	strhandler_operator(char *ptr, char *str, int *i, int *index)
{
	char	operator;

	if (!str || !ptr || !i || !index || !str[*i]) // Validate inputs
		return ;
	ptr[(*index)++] = SPACE;
	operator= str[*i];
	while (str[*i] && str[*i] == operator)
	{
		ptr[(*index)++] = str[*i];
		(*i)++;
	}
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
		return (NULL);
	ptr = malloc(size + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	while (line[i])
	{
		ft_skip_whitespace(line, &i);
		if (line[i] && isquotes(line[i])) // handler quotes
			strhandler_quotes(ptr, line, &i, &index);
		else if (line[i] && is_operator(line[i])) // handler operatoin
			strhandler_operator(ptr, line, &i, &index);
		else // handler word
			handlerword(ptr, line, &index, &i);
	}
	ptr[index] = '\0';
	return (ptr);
}

int	handle_input_syntax(t_string *st_string)
{
	t_env_lst	*head;

	head = NULL;
	st_string->strcon = handler_string(st_string->line);
	if (!st_string->strcon)
	{
		printf("Error: Failed to process input string.\n");
		return (0);
	}
	// printf("%s\n", st_string->strcon);
	ft_spliter(&head, st_string->strcon);
	if (!head)
	{
		printf("Error: No tokens generated.\n");
		return (0);
	}
	st_string->head = head;
	// print_lst_tokens(head); // Debug print
	execute_command(st_string);
	free_list(head);
	return (1);
}

void	start_shell_session(t_string st_string)
{
	while (1)
	{
		st_string.line = get_line();
		handle_input_syntax(&st_string);
		// exectoction();
		free(st_string.line);
		free(st_string.strcon);
		st_string.line = NULL;
	}
}