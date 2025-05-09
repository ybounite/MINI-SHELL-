/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:24:12 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/09 18:35:33 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../../includes/minishell.h"


int	lenqoutes(char *str, int *i)
{
	char	quotes;
	int		counter;
	int		start;

	counter = 0;
	if (*i - 1 > 0 && find_space(str[*i - 1]))
		counter++;
	quotes = str[(*i)++];
	start = *i;
	counter += skip_strqoutes(str, &start, quotes) + 1;
	*i = start;
	return (counter);
}

int	lenoperator(char *str, int *i)
{
    int		counter;
    char	operator;

    counter = 0;
    operator = str[*i];
    while (str[*i] && str[*i] == operator)
    {
        if (str[*i + 1] && ((operator == '>' && str[*i + 1] == '<')
            || (operator == '<' && str[*i + 1] == '>')))
            return (ft_puterror(operator), -1337);
        if (str[*i + 1] && operator == '|' && str[*i + 1] == '|')
            return (ft_puterror(operator), -1337); // error |> <|
        counter++;
        (*i)++;
        if (counter >= 3)
            return (ft_puterror(operator), -1337);
    }
    counter++;
    if (str[*i] && !find_space(str[*i]))
        counter++;
    ft_skip_whitespace(str, i);
    if (str[*i] && is_operator(str[*i]))
        return (ft_puterror(operator), -1337);
    return (counter);
}

bool	handler_syntax_error(char *line)
{
	if (is_first_operation_pipe(line) || is_last_operation_pipe(line))
		return (true);
	if (ft_lenword(line) < 0)
		return (true);
	return (false);
}
