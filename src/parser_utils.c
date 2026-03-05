/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_arg(t_cmd *cmd, char *word)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
		return ;
	i = -1;
	while (++i < cmd->arg_count)
		new_args[i] = cmd->args[i];
	new_args[i] = ft_strdup(word);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
}

void	cmd_add_redir(t_cmd *cmd, t_redir_type type, char *fname)
{
	t_redir	*r;
	t_redir	*last;

	r = malloc(sizeof(t_redir));
	if (!r)
		return ;
	r->type = type;
	r->filename = ft_strdup(fname);
	r->heredoc_fd = -1;
	r->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = r;
		return ;
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = r;
}
