/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:29:37 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/01 18:54:20 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_numeric(char *s)
{
	int i;

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

void builtin_exit(char **args, t_string *st_string)
{
	char ar[100];

	printf("exit\n");
	if (!args[1])
	{
		free_list(st_string->head);
		ft_malloc(0, 0);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		free_list(st_string->head);
		printf("exit: %s: numeric argument required\n", args[1]);
		ft_malloc(0, 0);
		exit(2);
	}
	if (args[2])
	{
		printf("exit: too many arguments\n");
		ft_malloc(0, 0);
		return;
	}
	ft_strlcpy(ar, args[1], ft_strlen(args[1]));
	free_list(st_string->head);
	ft_malloc(0, 0);
	exit(ft_atoi(ar));
}
