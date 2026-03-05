/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *s);

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_shell *sh)
{
	long long	n;

	write(2, "exit\n", 5);
	if (cmd->arg_count == 1)
	{
		sh->running = 0;
		return (sh->exit_status);
	}
	if (!is_numeric(cmd->args[1]))
	{
		print_error("exit", cmd->args[1],
			"numeric argument required");
		sh->running = 0;
		sh->exit_status = 2;
		return (2);
	}
	if (cmd->arg_count > 2)
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	n = ft_atoll(cmd->args[1]);
	sh->running = 0;
	sh->exit_status = (int)(n & 0xFF);
	return (sh->exit_status);
}
