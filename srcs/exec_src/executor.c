#include "../../includes/minishell.h"
#include "../libraries/libft/libft.h"

int	lstsize(t_env_lst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	**git_array(t_env_lst **list)
{
	char		**args;
	t_env_lst	*current;

	int i, count = 0;
	current = *list;
	if (current->type == PIPE)
		return (perror("minishell: parse error near `|'\n"), NULL);
	while (current && current->type != PIPE)
	{
		count++;
		current = current->next;
	}
	if (count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*list && (*list)->type != PIPE)
	{
		args[i++] = ft_strdup((*list)->value);
		*list = (*list)->next;
	}
	args[i] = NULL;
	return (args);
}

void	execute_command(t_string *st_string)
{
	execute_pipeline(st_string);
}
