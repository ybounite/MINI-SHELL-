#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

char	*collapse_spaces(const char *str)
{
	int		i;
	int		j;
	int		space_flag;
	char	*result;

	i = 0;
	j = 0;
	space_flag = 0;
	result = ft_malloc(ft_strlen(str) + 1, 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			if (!space_flag)
				result[j++] = ' ';
			space_flag = 1;
		}
		else
		{
			result[j++] = str[i];
			space_flag = 0;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
