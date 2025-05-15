/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:44:50 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 14:48:25 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_for_heredoc(int va_signal)
{
	if (va_signal == SIGINT)
	{
		write (1, "\n", 1);
		close(data_struc()->heredoc_fd);
		ft_malloc(false, false);
		exit(130);
	}
}

void	handler_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(130);
}

void	hendle_sigquit(int signum)
{
	(void)signum;
	exit(131);
}

void	assign_signals_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}
