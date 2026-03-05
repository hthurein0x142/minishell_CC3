/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_count(t_cmd *cmds)
{
	int	n;

	n = 0;
	while (cmds)
	{
		n++;
		cmds = cmds->next;
	}
	return (n);
}

void	executor(t_cmd *cmds, t_shell *sh)
{
	if (!cmds)
		return ;
	if (!cmds->args || !cmds->args[0])
	{
		if (cmds->redirs)
		{
			if (apply_redirections(cmds) == -1)
				sh->exit_status = 1;
			else
				sh->exit_status = 0;
		}
		return ;
	}
	if (cmd_count(cmds) == 1 && is_builtin(cmds->args[0]))
		exec_single_builtin(cmds, sh);
	else
		exec_pipeline(cmds, sh);
	close_heredocs(cmds);
}
