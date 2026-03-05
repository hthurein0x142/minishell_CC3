/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line(int fd, char *line, int expand, t_shell *sh)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_word(line, sh);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	read_heredoc_lines(int write_fd, char *delim,
	int do_expand, t_shell *sh)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_signal)
		{
			free(line);
			if (g_signal)
				return (-1);
			return (0);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			return (0);
		}
		write_heredoc_line(write_fd, line, do_expand, sh);
		free(line);
	}
}

static int	restore_stdin(int saved, int pipe_fd)
{
	dup2(saved, STDIN_FILENO);
	close(saved);
	if (pipe_fd >= 0)
		close(pipe_fd);
	return (-1);
}

static int	do_one_heredoc(t_redir *r, t_shell *sh)
{
	int		pfd[2];
	int		quoted;
	char	*clean_delim;
	int		ret;
	int		saved_stdin;

	if (pipe(pfd) == -1)
		return (-1);
	quoted = has_quotes(r->filename);
	if (quoted)
		clean_delim = strip_quotes(r->filename);
	else
		clean_delim = ft_strdup(r->filename);
	saved_stdin = dup(STDIN_FILENO);
	setup_signals_heredoc();
	g_signal = 0;
	ret = read_heredoc_lines(pfd[1], clean_delim, !quoted, sh);
	close(pfd[1]);
	free(clean_delim);
	if (ret == -1)
		return (restore_stdin(saved_stdin, pfd[0]));
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	r->heredoc_fd = pfd[0];
	return (0);
}

int	setup_heredocs(t_cmd *cmds, t_shell *sh)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
			{
				if (do_one_heredoc(r, sh) == -1)
				{
					close_heredocs(cmds);
					return (-1);
				}
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
