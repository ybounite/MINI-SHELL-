#include    "../../includes/minishell.h"

void	ft_puterror(char error)
{
	ft_putstr_fd("minishell: parse error near `", 2);
	if (error == '\n')
		ft_putstr_fd("newline", 2);
	else
		write(2, &error, 1);
	write(2, "\'\n", 2);
	data_struc()->is_error = 1;
}

int	skip_strqoutes(char *str, int *inedx, char quotes)
{
	int		counter;

	counter = 0;
	while (str[*inedx] && str[*inedx] != quotes)
	{
		(*inedx)++;
		counter++;
	}
	if (str[*inedx] == '\0') // ERROR();
		return (ft_puterror(quotes), -1337);
	if (str[*inedx] && str[*inedx] == quotes)
	{
		(*inedx)++;
		counter++;
	}
	return (counter);
}

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

bool	is_first_operation_pipe(char *str)
{
	int i = 0;
	ft_skip_whitespace(str, &i);
	if (str[i] == PIPE)
		ft_puterror('|');
	return (str[i] == '|');
}

char	ft_skip_whitquotes(char *str, int *index)
{
	char	quote;
	quote = str[(*index)++];
	while (str[*index] && str[*index] != quote)
		(*index)++;
	if (str[*index])
		(*index)++;
	return ('Q');
}

char	ft_skip_whitoperator(char *str, int *index)
{
	(*index)++;
	while (str[*index] && is_operator(str[*index]))
		(*index)++;
	return ('O');
}

char	ft_skip_whitword(char *str, int *index)
{
	while (str[*index] && !is_operator(str[*index])
		&& !isquotes(str[*index]) && !find_space(str[*index]))
		(*index)++;
	return ('W');
}

bool	is_last_operation_pipe(char *str)
{
	int		i;
	char	last_token_type;
	(1) && (i = 0), (last_token_type = 0);
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (!str[i])
			break;
		if (isquotes(str[i]))
			last_token_type = ft_skip_whitquotes(str, &i);
		else if (str[i] == PIPE)
		{
			i++;
			last_token_type = '|';
		}
		else if (is_operator(str[i]))
			last_token_type = ft_skip_whitoperator(str, &i);
		else
			last_token_type = ft_skip_whitword(str, &i);
	}
	if (last_token_type == '|')
		ft_puterror('|');
	if (last_token_type == 'O')
		ft_puterror('\n');
	return (last_token_type == 'O' || last_token_type == '|');
}

int	ft_lenword(char *str)
{
	int	(quote_len), (len), (i);
	(1) && (len = 0), (i = 0);
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (str[i] && isquotes(str[i]))
		{
			quote_len = lenqoutes(str, &i);
			if (quote_len < 0) // Error code for unmatched quotes
				return (-1);
			len += quote_len;
		}
		else if (str[i] && is_operator(str[i]))
			len += lenoperator(str, &i);
		else
		{
			while (str[i] && !is_operator(str[i]) && !isquotes(str[i])
				&& !find_space(str[i]))
			{
				if (i - 1 > 0 && find_space(str[i - 1]))
					len++;
				i++;
				len++;
			}
		}
		if (len < 0)
			break ;
	}
	return (len);
}
bool	handler_syntax_error(char *line)
{
	if (is_first_operation_pipe(line) || is_last_operation_pipe(line))
		return (true);
	if (ft_lenword(line) < 0)
		return (true);
	return (false);
}
