/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:08 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/29 09:44:26 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct s_string	*data_struc(void)
{
	static struct s_string	data_struc = {0};

	return (&data_struc);
}

char	**duplicate_envp(char **envp)
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
    ft_bzero(&st_string, sizeof(st_string));
    st_string.g_envp = duplicate_envp(envp);
    data_struc()->g_envp = st_string.g_envp;
    data_struc()->exit_status = 0; 
    assign_signals_handler();
    start_shell_session(st_string);
    ft_free_split(st_string.g_envp);
    return (0);
}
