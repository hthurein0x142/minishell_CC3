/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint_interactive(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}

static void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_interactive;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
