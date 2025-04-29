/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:26 by bamezoua          #+#    #+#             */
/*   Updated: 2025/04/29 11:26:53 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_string *st_string)
{
	int	i;

	i = 0;
	while (st_string->g_envp[i])
	{
		if (ft_strchr(st_string->g_envp[i], '='))
			printf("%s\n", st_string->g_envp[i]);
		i++;
	}
}
