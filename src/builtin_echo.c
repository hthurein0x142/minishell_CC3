/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (i < cmd->arg_count && is_n_flag(cmd->args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (i < cmd->arg_count)
	{
		printf("%s", cmd->args[i]);
		if (i + 1 < cmd->arg_count)
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
