/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_quote_state(char c, int *st)
{
	if (*st == 0 && c == '\'')
		return (*st = 1, 1);
	if (*st == 0 && c == '"')
		return (*st = 2, 1);
	if (*st == 1 && c == '\'')
		return (*st = 0, 1);
	if (*st == 2 && c == '"')
		return (*st = 0, 1);
	return (0);
}

static void	expand_args(t_cmd *cmd, t_shell *sh)
{
	char	*exp;
	int		i;

	i = -1;
	while (++i < cmd->arg_count)
	{
		exp = expand_word(cmd->args[i], sh);
		free(cmd->args[i]);
		cmd->args[i] = exp;
	}
}

static void	expand_redirs(t_cmd *cmd, t_shell *sh)
{
	t_redir	*r;
	char	*exp;

	r = cmd->redirs;
	while (r)
	{
		if (r->type != REDIR_HEREDOC)
		{
			exp = expand_word(r->filename, sh);
			free(r->filename);
			r->filename = exp;
		}
		r = r->next;
	}
}

void	expander(t_cmd *cmds, t_shell *sh)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		expand_args(cmd, sh);
		expand_redirs(cmd, sh);
		cmd = cmd->next;
	}
}
