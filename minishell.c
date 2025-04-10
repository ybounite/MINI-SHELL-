/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:08 by ybounite          #+#    #+#             */
/*   Updated: 2025/04/10 16:33:27 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_string	*data_struc(void)
{
	static struct s_string	data_struc = {0};

	return (&data_struc);
}

int	main(void)
{
	t_string	st_string;

	assign_signals_handler();
	start_shell_session(st_string);
}
