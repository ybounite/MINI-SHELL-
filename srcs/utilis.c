#include "../includes/minishell.h"

// char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	char	*result;

// 	result = ft_strjoin(s1, s2);
// 	free(s1);
// 	return (result);
// }

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
