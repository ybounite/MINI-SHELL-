/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:04:52 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/13 10:06:51 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_env_vars(char **env, int i, int j)
{
	char	*tmp;

	tmp = env[i];
	env[i] = env[j];
	env[j] = tmp;
}

static int	should_swap(char *str_i, char *str_j)
{
	size_t	len_i;
	size_t	len_j;

	len_i = ft_strlen(str_i);
	len_j = ft_strlen(str_j);
	if (len_i > len_j)
		return (ft_strncmp(str_i, str_j, len_j) > 0);
	else
		return (ft_strncmp(str_i, str_j, len_i) > 0);
}

void	sort_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (should_swap(env[i], env[j]))
				swap_env_vars(env, i, j);
			j++;
		}
		i++;
	}
}
