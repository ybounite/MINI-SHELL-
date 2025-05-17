/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:37 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/17 16:27:15 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char **args, t_string *st_string)
{
	int	exit_code;

	(void)st_string;
	printf("exit\n");
	if (!args[1])
	{
		ft_malloc(0, 0);
		exit(g_exit_status);
	}
	if (!is_numeric(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		ft_malloc(0, 0);
		exit(2);
	}
	if (args[2])
	{
		printf("exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	exit_code = ft_atoi(args[1]);
	exit_code = (unsigned char)exit_code;
	ft_malloc(0, 0);
	exit(exit_code);
}
