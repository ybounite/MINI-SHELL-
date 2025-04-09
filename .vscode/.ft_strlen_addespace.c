# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
// #include "libft/libft.h"

bool	find_space(char c);

bool is_operator(char c)
{
	return (c == '&' || c == '|' || c == '>' || c == '<');
}
bool	find_space(char c)
{
	return (c == SPACE || c == TAB || c == NEWLINE);
}
void	ft_skip_whitespace(char *str, int *index)
{
	while (str[*index] && find_space(str[*index]))
		(*index)++;
}
bool isquotes(char c)
{
	return (c == '\'' || c == '\"');
}
int	skip_strqoutes(char *str, int *inedx, char quotes)
{
	int counter;

	counter = 0;
	while (str[*inedx] && str[*inedx] != quotes)
	{
		(*inedx)++;
		counter++;
	}
	if (str[*inedx] && str[*inedx] == quotes){
		(*inedx)++;
		counter++;
	}
	return (counter);
}
int	skip_word(char *str, int *i)
{
	int count_word;

	count_word = 0;
	if (*i - 1 > 0 && find_space(str[*i - 1]))
		count_word++;
	while (str[*i] && !is_operator(str[*i]) && !isquotes(str[*i]))
	{
		(*i)++;
		count_word++;
	}
	return (count_word);
}
int	skip_operator(char *str, int *index, char operator)
{
	int	count_operator;

	count_operator = 0;
	while (str[*index] && str[*index] == operator)
	{
		(*index)++;
		count_operator++;
	}
	return (count_operator);
}
int	ft_lenword(char *str)
{
	int (len), (i);
	char quotes;
	char operator;
	len = 0;
	i = 0;
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		if (str[i] && isquotes(str[i]))
		{
			if (i - 1 > 0 && find_space(str[i - 1]))
				len++;
			quotes = str[i++];
			len += skip_strqoutes(str, &i, quotes) + 1;
		}
		else if (str[i] && is_operator(str[i])){
			len++;
			operator = str[i];
			while (str[i] && str[i] == operator)
			{
				len++;
				i++;
			}
			if (str[i] && !find_space(str[i]))
				len++;
		}
		else
		{
			while (str[i] && !is_operator(str[i]) && !isquotes(str[i]) && !find_space(str[i]))
			{
				if (i - 1 > 0 && find_space(str[i - 1]))
					len++;
				i++;
				len++;
			}
		}
	}
	return (len);
}

char *strdup_addespace(char *str)
{
	int i = 0;
	int index = 0;
	char operator;
	char quots;
	char *ptr;

	ptr  = malloc(ft_lenword(str) + 1 *sizeof(char));
	while (str[i])
	{
		ft_skip_whitespace(str, &i);
		// handler quotes 
		if (str[i] && isquotes(str[i])){
			if (i - 1 > 0 && find_space(str[i - 1]))
				ptr[index++] = SPACE;
			quots = str[i];
			ptr[index++] = str[i++];
			while (str[i] && str[i] != quots)
				ptr[index++] = str[i++];
			ptr[index++] = str[i++];
		}// handler operatoin 
		else if (str[i] && is_operator(str[i]))
		{
			ptr[index++] = SPACE;
			operator = str[i];//skip_oprator()
			while (str[i] && str[i] == operator)
			{
				ptr[index++] = str[i++];
				// calcal_howMayOperator();//and exit if mor 2;
			}
			if (str[i] && !find_space(str[i]))
				ptr[index++] = SPACE;
		}// handler word 
		else{
			if (i - 1 > 0 && find_space(str[i - 1]))
				ptr[index++] = SPACE;
			ptr[index++] = str[i++];
		}
	}
	ptr[index] = '\0';
	return ptr;
}

int main()
{
	char *len = "ls";
	char *str = strdup_addespace(len);
	printf("%s\n", str);
	free(str);
}
/*int	lenqoutes(char *str, int *i)
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

int lenoperator(char *str, int *i)
{
	int counter;
	char operator;

	counter = 0;
	operator = str[*i];//save operator
	while (str[*i] && str[*i] == operator)
	{
		if (operator == '>' && str[*i + 1] == '<')
			return (ft_error_quotes(operator), 0);
		else if (operator == '<' && str[*i + 1] == '>')
			return (printf(": parse error near `\n'\n"), 0);
		counter++;
		(*i)++;
		if (counter >= 3)
			return (ft_error_quotes(operator), 0);
	}
	counter++;// add space after operator 
	if (str[*i] && !find_space(str[*i]))
		counter++;
	return (counter);
}*/