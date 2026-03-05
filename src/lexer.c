/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char	*read_word(char *input, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& !is_meta(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_strndup(input + start, *i - start));
}

static t_token	*read_operator(char *input, int *i)
{
	if (input[*i] == '|')
		return ((*i)++, new_token(TOKEN_PIPE, ft_strdup("|")));
	if (input[*i] == '<' && input[*i + 1] == '<')
		return ((*i) += 2, new_token(TOKEN_HEREDOC, ft_strdup("<<")));
	if (input[*i] == '<')
		return ((*i)++, new_token(TOKEN_REDIR_IN, ft_strdup("<")));
	if (input[*i] == '>' && input[*i + 1] == '>')
		return ((*i) += 2, new_token(TOKEN_APPEND, ft_strdup(">>")));
	return ((*i)++, new_token(TOKEN_REDIR_OUT, ft_strdup(">")));
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	t_token	*tok;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			i++;
			continue ;
		}
		if (is_meta(input[i]))
			tok = read_operator(input, &i);
		else
			tok = new_token(TOKEN_WORD, read_word(input, &i));
		if (!tok)
		{
			free_tokens(tokens);
			return (NULL);
		}
		token_add_back(&tokens, tok);
	}
	return (tokens);
}
