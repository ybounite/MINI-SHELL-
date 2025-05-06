#include    "../../includes/minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	find_space(char c)
{
	return (c == SPACE || c == TAB || c == NEWLINE);
}

bool	isquotes(char c)
{
	return (c == '\'' || c == '\"');
}

void	ft_skip_whitespace(char *str, int *index)
{
	while (str[*index] && find_space(str[*index]))
		(*index)++;
}

bool	isemtyqoutes(char *str, int i)
{
	char	qouts;
	int		len;

	len = 0;
	qouts = str[i++];
	while (str[i] && str[i] != qouts)
	{
		i++;
		len++;
	}
	return (len == 0);
}
