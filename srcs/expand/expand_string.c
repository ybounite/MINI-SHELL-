/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:12 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/14 13:16:38 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_dollar_digit(char *result, int *i)
{
	*i += 2;
	return (result);
}

static char	*handle_double_dollar(char *result, int *i)
{
	char	*temp;

	temp = result;
	result = ft_strjoin(result, "$$");
	*i += 2;
	return (result);
}

static char	*handle_quoted_dollar(char *result, const char *str, int *i)
{
	int		j;
	char	*quoted_content;
	char	*temp;

	j = *i + 2;
	while (str[j] && str[j] != '"')
		j++;
	quoted_content = ft_substr(str, *i + 2, j - (*i + 2));
	temp = result;
	result = ft_strjoin(result, quoted_content);
	if (str[j] == '"')
		*i = j + 1;
	else
		*i = j;
	return (result);
}

static char	*handle_variable(char *result, const char *str, int *i,
		bool *is_spliting)
{
	char	*var_name;
	char	*var_value;
	int		original_i;

	original_i = *i;
	var_name = get_variable_name(str, i);
	if (var_name)
	{
		var_value = get_variable_value(var_name);
		if (!is_spliting[0] && !is_spliting[1])
			*is_spliting = 1;
		result = ft_strjoin(result, var_value);
		if (original_i == *i)
		{
			result = ft_strjoin_char(result, '$');
			(*i)++;
		}
	}
	else if (str[*i + 1] != '"')
	{
		result = ft_strjoin_char(result, '$');
		(*i)++;
	}
	return (result);
}

// quotes[0] = 0; // single quotes && quotes[1] = 0; // double quotes
char	*expand_string(const char *str, bool *is_spliting)
{
	int		i;
	bool	quotes[2];
	char	*result;

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	result = ft_strdup("");
	while (str[i])
	{
		printf("str[i] : %c\n", str[i]);
		if (str[i] == '$' && ft_isdigit(str[i + 1]) && !quotes[0])
			result = handle_dollar_digit(result, &i);
		else if (str[i] == '$' && str[i + 1] == '$')
			result = handle_double_dollar(result, &i);
		else if (str[i] == '\'' && !quotes[1])
			result = handle_single_quote(result, str, &i, &quotes[0]);
		else if (str[i] == '\"' && !quotes[0])
			result = handle_double_quote(result, str, &i, &quotes[1]);
		else if (str[i] == '$' && !quotes[0])
		{
			if (str[i + 1] == '"')
				result = handle_quoted_dollar(result, str, &i);
			else
				result = handle_variable(result, str, &i, is_spliting);
		}
		else
		{
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
	}
	return (result);
}
