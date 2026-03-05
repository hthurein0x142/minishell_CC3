/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_fds(int in_fd, int *pfd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (pfd && pfd[1] >= 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		if (pfd[0] >= 0)
			close(pfd[0]);
		close(pfd[1]);
	}
}

static void	do_execve(t_cmd *cmd, t_shell *sh)
{
	char	**envp;
	char	*path;

	path = resolve_path(cmd->args[0], sh);
	if (!path)
	{
		print_error(cmd->args[0], NULL, "command not found");
		exit(127);
	}
	envp = env_to_array(sh->env);
	execve(path, cmd->args, envp);
	print_error(cmd->args[0], NULL, strerror(errno));
	env_free_array(envp);
	free(path);
	exit(126);
}

void	exec_child(t_cmd *cmd, t_shell *sh, int in_fd, int *pfd)
{
	setup_signals_child();
	setup_child_fds(in_fd, pfd);
	if (apply_redirections(cmd) == -1)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, sh));
	do_execve(cmd, sh);
}

void	exec_child_proc(t_cmd *cmd, t_shell *sh, int in_fd, int *pfd)
{
	if (cmd->next)
		exec_child(cmd, sh, in_fd, pfd);
	else
		exec_child(cmd, sh, in_fd, NULL);
}
