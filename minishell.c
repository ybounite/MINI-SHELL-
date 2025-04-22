/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:08 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/22 18:46:28 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

struct s_string	*data_struc(void)
{
	static struct s_string	data_struc = {0};

	return (&data_struc);
}

static char	**duplicate_envp(char **envp)
{
	int		i;
	int		len;
	char	**new_envp;

	len = 0;
	while (envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_string	st_string;

	(void)argc;
	(void)argv;
	st_string.g_envp = duplicate_envp(envp);
	if (!st_string.g_envp)
		return (perror("Failed to initialize environment"), 1);
	assign_signals_handler();
	start_shell_session(st_string);
	ft_free_split(st_string.g_envp);
	return (0);
}
