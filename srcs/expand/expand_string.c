/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:12 by bamezoua          #+#    #+#             */
/*   Updated: 2025/05/18 20:01:39 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (!*is_spliting)
			*is_spliting = 1;
		result = ft_strjoin(result, var_value);
		if (original_i == *i)
		{
			result = ft_strjoin_char(result, '$');
			(*i)++;
		}
	}
	else
	{
		result = ft_strjoin_char(result, '$');
		(*i)++;
	}
	return (result);
}

static char	*process_character(const char *str, int *i, t_expand_context *ctx)
{
	if (str[*i] == '$' && ft_isdigit(str[*i + 1]) && !ctx->quotes[0])
		ctx->result = handle_dollar_digit(ctx->result, i);
	else if (str[*i] == '$' && str[*i + 1] == '$')
		ctx->result = handle_double_dollar(ctx->result, i);
	else if (str[*i] == '\'' && !ctx->quotes[1])
		ctx->result = handle_single_quote(ctx->result, str, i, &ctx->quotes[0]);
	else if (str[*i] == '\"' && !ctx->quotes[0])
		ctx->result = handle_double_quote(ctx->result, str, i, &ctx->quotes[1]);
	else if (str[*i] == '$' && !ctx->quotes[0])
	{
		if (str[*i + 1] == '"' && !ctx->quotes[1])
			ctx->result = handle_quoted_dollar(ctx->result, str, i);
		else
			ctx->result = handle_variable(ctx->result, str, i,
					ctx->is_spliting);
	}
	else
	{
		ctx->result = ft_strjoin_char(ctx->result, str[*i]);
		(*i)++;
	}
	return (ctx->result);
}

char	*expand_string(const char *str, bool *is_spliting)
{
	int					i;
	t_expand_context	ctx;

	i = 0;
	ctx.quotes[0] = 0;
	ctx.quotes[1] = 0;
	ctx.is_spliting = is_spliting;
	ctx.result = ft_strdup("");
	while (str[i])
		ctx.result = process_character(str, &i, &ctx);
	if (ft_strchr(ctx.result, '|') && is_spliting)
		*is_spliting = false;
	return (ctx.result);
}
