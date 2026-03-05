/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_err(char *near)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, near, ft_strlen(near));
	write(2, "'\n", 2);
	return (1);
}

int	check_syntax(t_token *tokens)
{
	t_token	*tok;

	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_PIPE)
		return (syntax_err("|"));
	tok = tokens;
	while (tok)
	{
		if (tok->type == TOKEN_PIPE && (!tok->next
				|| tok->next->type == TOKEN_PIPE))
			return (syntax_err("|"));
		if ((tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_APPEND)
			&& (!tok->next || tok->next->type != TOKEN_WORD))
		{
			if (tok->next)
				return (syntax_err(tok->next->value));
			return (syntax_err("newline"));
		}
		tok = tok->next;
	}
	return (0);
}

static t_redir_type	tok_to_redir(t_token_type t)
{
	if (t == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (t == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (t == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_APPEND);
}

static void	parse_token(t_cmd **cur, t_token **tok)
{
	if ((*tok)->type == TOKEN_WORD)
		cmd_add_arg(*cur, (*tok)->value);
	else if ((*tok)->type == TOKEN_PIPE)
	{
		(*cur)->next = new_cmd();
		*cur = (*cur)->next;
	}
	else
	{
		cmd_add_redir(*cur, tok_to_redir((*tok)->type),
			(*tok)->next->value);
		*tok = (*tok)->next;
	}
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cur;
	t_token	*tok;

	if (check_syntax(tokens))
		return (NULL);
	head = new_cmd();
	cur = head;
	tok = tokens;
	while (tok)
	{
		parse_token(&cur, &tok);
		tok = tok->next;
	}
	return (head);
}
