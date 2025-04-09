/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:43:56 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/07 21:34:35 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_string	*data_struc(void)
{
	static struct s_string	data_struc = {0};

	return (&data_struc);
}

en_status_type stats_type(char c)
{
	if (c == DOUBLE_QUOTE)
		return DOUBLE_QUOTE;
	else
		return SINGLE_QUOTE;
}

void	handler_quotes(t_env_lst **head, char *str,int *index)
{
	char	char_quote;
	char	*tokes;
	int		start;

	start = *index;
	char_quote = str[*index];
	(*index)++;
	while (str[*index] && str[*index] != char_quote)
		(*index)++;
	if (str[(*index)] != char_quote)
	{
		printf("minishell : parse error near '%c'\n", char_quote);
		// data->error = 1;
		return ;
	}
	tokes = ft_substr(str, start + 1, (*index) - start - 1);
	add_lst_token(head, tokes, stats_type(char_quote), same_string(str, index, char_quote));
	(*index)++;
}

en_status_type check_stats_type(char *str)
{
	if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (REDIRECTION);
	else if (!ft_strcmp(str, "(") || !ft_strcmp(str, "("))
		return (PARENTHESIS);
	else
		return (CMD);
}

int	counter_operator(char *str, int i, char c)
{
	int counter;

	counter = 0;
	while (str[i] && str[i] == c)
	{
		i++;
		counter++;
	}
	return (counter);
}

void	handler_other_operator(t_env_lst ** head, char *str, int *index, en_status_type state)
{
	char	c;
	char	*token;
	int		j;
	int		start;

	c = str[(*index)];
	j = counter_operator(str, *index, c);
	start = *index;
	while (str[(*index)] && str[(*index)] == c)
		(*index)++;
	if (c == '&' && j == 1)
		j = 3;
	if (j > 2)
	{
		printf("minishell : parse error near '%c'\n", c);
		return ;
	}
	token = ft_substr(str, start, (*index) - start);
	add_lst_token(head, token, state, 1);
}

int main()
{
	t_string	input;
	data_struc()->exit_status = 10;
	start_shell_session(input); //start in shell
	return 0;
}
