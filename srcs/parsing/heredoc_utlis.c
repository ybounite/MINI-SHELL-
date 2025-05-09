/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:36:52 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/09 18:22:26 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_isheredoc(t_env_lst *list)
{
	while (list)
	{
		if (list->type == HERE_DOCUMENT)
			return (true);
		list = list->next;
	}
	return (false);
}

char	*creatr_file_name(int fd)
{
	char	*file_name;
	char	characte[1];
	int		is_filled;
	int 	i;
	
	i = 0;
	file_name = ft_malloc(10 *sizeof(char) , true);
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
		return (perror("filled read"), NULL);
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
	printf("file name herdoc : %s\n", heredoc_file);
	fd = open(heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	data_struc()->heredoc_file = heredoc_file;
	if (fd < 0)
		return (-1);
	return (fd);
}

bool	is_quotes_thes_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isquotes(str[i]))
			return (true);
		i++;
	}
	return (false);
}

int	ft_lenofwords(char *str)
{
	char	qoutes;
	int		len;
	int		start;
	len = 0;
	start = 0;
	while (str[start] && str[start] != SPACE)
	{
		if (isquotes(str[start]))
		{
			qoutes = str[start++];
			while (str[start] && str[start] != qoutes)
			{
				start++;
				len++;
			}
			start++;
		}
		else
		{
			while (str[start] && !isquotes(str[start]) && str[start] != SPACE)
			{
				start++;
				len++;	
			}
		}
	}
	return (len);
}

char	*ft_remove_quotes(char *str)
{
	char	*ptr;
	char	quotes;
	int		index;
	int		i;

	(1) && (i = 0) , (index = 0);
	ptr = ft_malloc(ft_lenofwords(str) + 1, 1);
	while (str[i] && index < ft_lenofwords(str))
	{
		if (isquotes(str[i]))
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				ptr[index++] = str[i++];
			if (isquotes(str[i]))
				i++;
		}
		else
		{
			while (str[i] && !isquotes(str[i]) && str[i] != SPACE)
				ptr[index++] = str[i++];
		}
	}
	ptr[index] = '\0';
	return (ptr);
}

char	*find_delimiter(t_env_lst *list, int *is_expand)
{
	char	*delimiter;
	if (!is_quotes_thes_str(list->value))
		*is_expand = 1;
	delimiter = ft_remove_quotes(list->value);
	return (delimiter);
}

bool	ft_clculate_heredoc(t_env_lst	*list)
{
	int	size;
	
	size = 0;
	while(list)
	{
		if(list->type == HERE_DOCUMENT)
			size++;
		else if (list->type == PIPE)
			size = 0;
		list = list->next;
	}
	if (size > 16)
		return (ft_putendl_fd("maximum here-document count exceeded", 2),
			ft_malloc(0, 0), exit(2), false);// leaks of list
	return (true);
}
