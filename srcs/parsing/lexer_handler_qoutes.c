/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_qoutes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:49:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/05/05 16:28:44 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	lenofwords_qoutes(char *str, int start)
// {
// 	int		len;
// 	char	qoutes;
// 	len = 0;
// 	while (str[start] && str[start] != SPACE)
// 	{
// 		if (isquotes(str[start]))
// 		{
// 			qoutes = str[start++];
// 			while (str[start] && str[start] != qoutes)
// 			{
// 				start++;
// 				len++;
// 			}
// 			start++;
// 		}
// 		else
// 		{
// 			while (str[start] && !isquotes(str[start]) && str[start] != SPACE)
// 			{
// 				start++;
// 				len++;	
// 			}
// 		}
// 	}
// 	return (len);
// }
// void	handler_qoutes(t_env_lst **list, char *str, int *i, en_status state)
// {
// 	char	*ptr;
// 	char	quotes;
// 	int		index;
// 	int		len;

// 	(1) && (index = 0), (len = lenofwords_qoutes(str, *i));
// 	if (len == 0)
// 	{
// 		ft_add_newtoken(list, ft_strdup("\"\""), state);
// 		(*i) += 2;
// 		return;
// 	}
// 	// Handle quoted string with $ inside
// 	if (str[*i] == DOUBLE_QUOTE && ft_strchr(str + *i, '$'))// config in leakes
// 	// {
// 	// 	process_quoted_string_with_expansion(list, str, i, state);
// 	// 	return ;
// 	// }
// 	// Original code for handling other cases
// 	ptr = ft_malloc((len + 1) * sizeof(char), 1);
// 	while (str[*i] && index < len)
// 	{
// 		if (isquotes(str[*i]))
// 		{
// 			quotes = str[(*i)++];
// 			while (str[*i] && str[*i] != quotes)
// 				ptr[index++] = str[(*i)++];
// 			(*i)++;
// 		}
// 		else
// 		{
// 			while (str[*i] && !isquotes(str[*i]) && str[*i] != SPACE)
// 				ptr[index++] = str[(*i)++];
// 		}
// 	}
// 	ptr[index] = '\0';
// 	ft_add_newtoken(list, ptr, state);
// }

// // New function to handle quoted strings with variable expansion
// void process_quoted_string_with_expansion(t_env_lst **list, char *str, int *i, en_status state)
// {
// 	char	quotes = str[(*i)++]; // Store quote type and advance past it
// 	char	*result = ft_strdup(""); // Start with empty string
	
// 	while (str[*i] && str[*i] != quotes)
// 	{
// 		if (str[*i] == '$')
// 		{
// 			(*i)++; // Skip the $			
// 			// Get the variable name
// 			char	*var_name = NULL;
// 			int	var_len = lendollar(str, *i);
// 			if (var_len > 0)
// 			{
// 				var_name = malloc((var_len + 1) * sizeof(char));
// 				if (!var_name)
// 				{
// 					free(result);
// 					return;
// 				}
// 				// Copy variable name
// 				int j = 0;
// 				while (j < var_len)
// 					var_name[j++] = str[(*i)++];
// 				var_name[j] = '\0';
// 				// Get variable value
// 				char	*var_value = handler_expasion(var_name);
// 				// Append value to result
// 				char	*temp = result;
// 				result = ft_strjoin(result, var_value);
// 				free(temp);
// 				free(var_value);
// 				free(var_name);
// 			}
// 			else if (str[*i - 1] == '$')
// 			{
// 				// Handle lone $ character
// 				char *temp = result;
// 				result = ft_strjoin(result, "$");
// 				free(temp);
// 			}
// 		}
// 		else
// 		{
// 			// Regular text - collect until $ or end of quote
// 			int	text_start = *i;
// 			while (str[*i] && str[*i] != quotes && str[*i] != '$')
// 				(*i)++;
// 			// Extract this text chunk
// 			int chunk_len = *i - text_start;
// 			if (chunk_len > 0)
// 			{
// 				char *chunk = malloc((chunk_len + 1) * sizeof(char));
// 				if (!chunk)
// 				{
// 					free(result);
// 					return;
// 				}
// 				// Copy chunk
// 				strncpy(chunk, str + text_start, chunk_len);
// 				chunk[chunk_len] = '\0';
// 				// Append to result
// 				char *temp = result;
// 				result = ft_strjoin(result, chunk);
// 				free(temp);
// 				free(chunk);
// 			}
// 		}
// 	}
// 	if (str[*i] == quotes)
// 		(*i)++; // Skip closing quote
// 	ft_add_newtoken(list, result, state);
// }
