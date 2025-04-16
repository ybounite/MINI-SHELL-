#include "../includes/minishell.h"

void	print_env_entry(char *entry)
{
	char	*sep;
	int		key_len;

	sep = ft_strchr(entry, '=');
	if (sep)
	{
		key_len = sep - entry;
		printf("declare -x ");
		fwrite(entry, 1, key_len, stdout);
		printf("=\"%s\"\n", sep + 1);
	}
	else
		printf("declare -x %s\n", entry);
}

void	print_export(char **envp)
{
	int		i;
	char	**copy;

	copy = create_sorted_env_copy(envp);
	if (!copy)
		return ;
	i = 0;
	while (copy[i])
	{
		print_env_entry(copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
}
