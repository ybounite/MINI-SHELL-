#include "../includes/minishell.h"

/* Add a character to the result string */
char	*append_char(char *str, char c)
{
	char *new_str;
	int len;

	len = str ? ft_strlen(str) : 0;
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	if (str)
		ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}