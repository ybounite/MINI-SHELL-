/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatr_file_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:58:37 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/10 09:59:27 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*creatr_file_name(int fd)
{
	char	*file_name;
	char	characte[1];
	int		is_filled;
	int		i;
	
	i = 0;
	file_name = ft_malloc(10 *sizeof(char), true);
	while (i < 9)
	{
		is_filled = read(fd, characte, 1);
		if (ft_isalpha(characte[0]))
		{
			file_name[i] = characte[0];
			i++;
		}
	}
	file_name[i] = '\0';
	return (file_name);
}

char	*create_temp_file()
{
	int		fd;
	char	*file_name;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (perror("filled to open in file\n"), NULL);
	file_name = creatr_file_name(fd);
	if (!file_name)
		return (NULL);
	close(fd);
	return (file_name);
}

int	open_heredoc()
{
	int		fd;
	char	*file_name;
	char	*heredoc_file;

	while (true)
	{
		file_name = create_temp_file();
		if (!file_name)
			return (-1);
		heredoc_file = ft_strjoin("/tmp/", file_name);
		if (!heredoc_file)
			return (-1);
		if (access(heredoc_file, F_OK) != 0)
			break;
	}
	fd = open(heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	data_struc()->heredoc_file = heredoc_file;
	if (fd < 0)
		return (-1);
	return (fd);
}
