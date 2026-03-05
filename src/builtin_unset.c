/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_cmd *cmd, t_shell *sh)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (i < cmd->arg_count)
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			print_error("unset", cmd->args[i],
				"not a valid identifier");
			ret = 1;
		}
		else
			env_unset(&sh->env, cmd->args[i]);
		i++;
	}
	return (ret);
}
