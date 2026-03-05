/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_redir_in(t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(r->filename, NULL, strerror(errno));
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	apply_redir_out(t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(r->filename, NULL, strerror(errno));
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_redir_append(t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(r->filename, NULL, strerror(errno));
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_redir_heredoc(t_redir *r)
{
	if (r->heredoc_fd < 0)
		return (-1);
	dup2(r->heredoc_fd, STDIN_FILENO);
	close(r->heredoc_fd);
	r->heredoc_fd = -1;
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN && apply_redir_in(r) == -1)
			return (-1);
		else if (r->type == REDIR_OUT && apply_redir_out(r) == -1)
			return (-1);
		else if (r->type == REDIR_APPEND && apply_redir_append(r) == -1)
			return (-1);
		else if (r->type == REDIR_HEREDOC
			&& apply_redir_heredoc(r) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}
