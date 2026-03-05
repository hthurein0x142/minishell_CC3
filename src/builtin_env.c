/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *sh)
{
	t_env	*cur;

	cur = sh->env;
	while (cur)
	{
		if (cur->has_value)
		{
			if (cur->value)
				printf("%s=%s\n", cur->key, cur->value);
			else
				printf("%s=\n", cur->key);
		}
		cur = cur->next;
	}
	return (0);
}
