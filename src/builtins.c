/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "history") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_shell *sh)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd, sh));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd, sh));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd, sh));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(sh));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd, sh));
	if (ft_strcmp(cmd->args[0], "history") == 0)
		return (builtin_history());
	return (1);
}
