/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_children(pid_t last_pid, int n)
{
	int		status;
	int		ret;
	int		i;

	ret = 0;
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = 128 + WTERMSIG(status);
	i = 1;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
	return (ret);
}

static pid_t	fork_cmd(t_cmd *cmd, t_shell *sh, int in_fd, int *new_in)
{
	int		pfd[2];
	pid_t	pid;

	pfd[0] = -1;
	pfd[1] = -1;
	if (cmd->next && pipe(pfd) == -1)
	{
		perror("minishell: pipe");
		return (-2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-2);
	}
	if (pid == 0)
		exec_child_proc(cmd, sh, in_fd, pfd);
	if (in_fd != STDIN_FILENO && in_fd >= 0)
		close(in_fd);
	if (pfd[1] >= 0)
		close(pfd[1]);
	*new_in = pfd[0];
	return (pid);
}

void	exec_pipeline(t_cmd *cmds, t_shell *sh)
{
	int		in_fd;
	pid_t	last_pid;
	int		n;
	t_cmd	*cmd;
	pid_t	pid;

	in_fd = STDIN_FILENO;
	n = 0;
	last_pid = -1;
	cmd = cmds;
	setup_signals_ignore();
	while (cmd)
	{
		pid = fork_cmd(cmd, sh, in_fd, &in_fd);
		if (pid == -2)
			return ;
		last_pid = pid;
		n++;
		cmd = cmd->next;
	}
	if (in_fd != STDIN_FILENO && in_fd >= 0)
		close(in_fd);
	sh->exit_status = wait_children(last_pid, n);
}

void	exec_single_builtin(t_cmd *cmd, t_shell *sh)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) == -1)
	{
		sh->exit_status = 1;
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return ;
	}
	sh->exit_status = exec_builtin(cmd, sh);
	fflush(stdout);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
