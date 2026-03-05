/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *arg, char *msg)
{
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
	}
	if (msg)
	{
		write(2, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	write(2, "\n", 1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

static void	free_redirs(t_redir *r)
{
	t_redir	*rtmp;

	while (r)
	{
		rtmp = r->next;
		if (r->heredoc_fd >= 0)
			close(r->heredoc_fd);
		free(r->filename);
		free(r);
		r = rtmp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->args)
		{
			i = -1;
			while (cmds->args[++i])
				free(cmds->args[i]);
			free(cmds->args);
		}
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

void	free_shell(t_shell *sh)
{
	env_free_list(sh->env);
	sh->env = NULL;
}
