/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_history(void)
{
	HIST_ENTRY	**list;
	int			i;

	list = history_list();
	if (!list)
		return (0);
	i = 0;
	while (list[i])
	{
		printf("%5d  %s\n", i + 1, list[i]->line);
		i++;
	}
	return (0);
}
