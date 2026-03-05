/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	process_line(char *line, t_shell *sh)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return ;
	cmds = parser(tokens);
	if (!cmds)
	{
		sh->exit_status = 2;
		free_tokens(tokens);
		return ;
	}
	expander(cmds, sh);
	if (setup_heredocs(cmds, sh) == -1)
	{
		sh->exit_status = 130;
		free_cmds(cmds);
		free_tokens(tokens);
		return ;
	}
	executor(cmds, sh);
	free_cmds(cmds);
	free_tokens(tokens);
}

static void	check_signal_status(t_shell *sh)
{
	if (g_signal)
	{
		sh->exit_status = 128 + g_signal;
		g_signal = 0;
	}
}

static void	handle_sigint_readline(t_shell *sh)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	sh->exit_status = 130;
	g_signal = 0;
}

static void	read_and_process(t_shell *sh)
{
	char	*line;
	char	*prompt;

	setup_signals_interactive();
	prompt = ft_strdup("./minishell>> ");
	line = readline(prompt);
	free(prompt);
	if (!line && g_signal == SIGINT)
	{
		handle_sigint_readline(sh);
		return ;
	}
	if (!line)
	{
		write(1, "exit\n", 5);
		sh->running = 0;
		return ;
	}
	check_signal_status(sh);
	if (*line)
	{
		add_history(line);
		process_line(line, sh);
	}
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh.env = env_init(envp);
	sh.exit_status = 0;
	sh.running = 1;
	while (sh.running)
		read_and_process(&sh);
	rl_clear_history();
	free_shell(&sh);
	return (sh.exit_status);
}
