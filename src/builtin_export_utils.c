/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_count(t_env *env)
{
	int	cnt;

	cnt = 0;
	while (env)
	{
		cnt++;
		env = env->next;
	}
	return (cnt);
}

t_env	*env_find_min(t_env *env, t_env **visited, int v_count)
{
	t_env	*min;
	int		i;

	min = NULL;
	while (env)
	{
		i = 0;
		while (i < v_count && visited[i] != env)
			i++;
		if (i == v_count && (!min || ft_strcmp(env->key, min->key) < 0))
			min = env;
		env = env->next;
	}
	return (min);
}

void	print_one_export(t_env *min)
{
	printf("declare -x %s", min->key);
	if (min->has_value)
	{
		if (min->value)
			printf("=\"%s\"", min->value);
		else
			printf("=\"\"");
	}
	printf("\n");
}
