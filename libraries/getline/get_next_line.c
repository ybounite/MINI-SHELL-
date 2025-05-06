/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:14:22 by ybounite          #+#    #+#             */
/*   Updated: 2024/11/24 18:18:10 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strchar(char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*chack_if_newline(char *line)
{
	size_t	i;
	char	*remainder;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	remainder = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	line[i + 1] = '\0';
	if (remainder && remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	return (remainder);
}

static char	*ft_full_buffer_line(int fd, char *buffer, char *remaider)
{
	ssize_t	read_char;
	char	*ptr;

	while (1)
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(remaider);
			return (remaider = NULL, NULL);
		}
		else if (read_char == 0)
			break ;
		buffer[read_char] = '\0';
		if (!remaider)
			remaider = ft_strdup("");
		ptr = remaider;
		remaider = ft_strjoin(ptr, buffer);
		free(ptr);
		ptr = NULL;
		if (ft_strchar(buffer, '\n'))
			break ;
	}
	return (remaider);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		//free(remainder);
		remainder = NULL;
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (free(remainder), remainder = NULL, NULL);
	line = ft_full_buffer_line(fd, buffer, remainder);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (free(line), line = NULL, NULL);
	remainder = chack_if_newline(line);
	return (line);
}
/*static char	*ft_full_buffer_line(int fd, char *buffer, char *remaider)
{
	ssize_t	read_char;
	char	*ptr;
	
	while (1)
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char == -1)
			return (NULL);
		else if (read_char == 0)
			break ;
		buffer[read_char] = '\0';
		if (!remaider)
			remaider = ft_strdup("");
		ptr = remaider;
		remaider = ft_strjoin(ptr, buffer);
		free(ptr);
		ptr = NULL;
		if (ft_strcherch(buffer, '\n'))
			break;
	}
	return (remaider);
}
char *chack_if_newline(char line)
{
	size_t i;
	char *ptr;

	while (line[i] && linr[i] != '\n')
		i++;
	if (line[i] == '\0' && line[i + 1] == '\0')
		return (NULL);
	ptr = ft_substr(line, i + 1, ft_strlen(line) - i)
	i = 0;
	return (ptr);
}
char	*get_next_line(int fd)
{
	static	char	*remainder;
	char	*buffer;
	char	*line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || read(1, 0, 0) == -1 || !buffer)
	{
		free(buffer);
		remainder = NULL;
		return (NULL);
	}
	line = ft_full_buffer_line(fd, buffer, remainder);
	if (!line)
		return (frre(line), NULL);
	remainder = chack_if_newline(line);
	return (line);
} */
