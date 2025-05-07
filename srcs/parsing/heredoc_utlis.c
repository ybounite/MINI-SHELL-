/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:36:52 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/07 09:58:29 by ybounite         ###   ########.fr       */
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

int	open_heredoc()
{
	int		fd;
	char	*heredoc_file;
	char	*index_str;
	int		i;

	i = 42;
	while (true)
	{
		index_str = ft_itoa(i);// leaks Error
		if (!index_str)
			return (-1);
		
		heredoc_file = ft_strjoin("/tmp/.heredoc_", index_str);
		if (!heredoc_file)
			return (-1);
		if (access(heredoc_file, F_OK) != 0)
			break;
		i++;
	}
	fd = open(heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	int fd1 = open(heredoc_file, O_RDONLY);
	unlink(heredoc_file);// delete in file 
	data_struc()->heredoc_file = heredoc_file;
	if (fd < 0)
		return (-1);
	return (fd1);
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

// void	handler_words(t_env_lst **list)
// {
// 	int		index;
// 	char	*ptr;
// 	int		len;
// 	char	qouts;
// 	(1) && (index = 0), (len = lentword(str, 0));
// 	if (len == 0)
// 		return ;
// 	ptr = ft_malloc((len + 1) * sizeof(char), 1);
// 	while (str[*i] && str[*i] != SPACE)
// 	{
// 		if (isquotes(str[*i]))
// 		{
// 			qouts = str[(*i)++];
// 			while (str[*i] && str[*i] != qouts)
// 				ptr[index++] = str[(*i)++];
// 			(*i)++;
// 		}
// 		else
// 			ptr[index++] = str[(*i)++];
// 	}
// 	ptr[index] = '\0';
// 	// strhandler_expansion(str, *i - index);
// 	ft_add_newtoken(list, ptr, state);
// }

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
	if (is_quotes_thes_str(list->value))
		*is_expand = 1;
	delimiter = ft_remove_quotes(list->value);
	printf("delimite : %s\n", delimiter);
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
			ft_malloc(0, 0), ft_destroylist(list), exit(2), false);// leaks of list
	return (true);
}
