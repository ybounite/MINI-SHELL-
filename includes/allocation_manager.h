/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_manager.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:32:08 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/15 16:16:35 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_MANAGER_H
# define ALLOCATION_MANAGER_H

# include "../libraries/libft/libft.h"

/* -------------------------------------------------------------------------- */
/*                               allocate_data.c                              */
/* -------------------------------------------------------------------------- */
void						*ft_malloc(size_t size, short option);
void						memory_released(t_list **head);

#endif