/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing(t_env *cur, const char *val, int hv)
{
	if (hv)
	{
		free(cur->value);
		if (val)
			cur->value = ft_strdup(val);
		else
			cur->value = ft_strdup("");
		cur->has_value = 1;
	}
	return (0);
}

static t_env	*create_node(const char *key, const char *val, int hv)
{
	if (hv)
	{
		if (val)
			return (env_new_node(key, val, hv));
		else
			return (env_new_node(key, "", hv));
	}
	return (env_new_node(key, NULL, hv));
}

int	env_set(t_env **env, const char *key, const char *val, int hv)
{
	t_env	*cur;
	t_env	*node;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (update_existing(cur, val, hv));
		cur = cur->next;
	}
	node = create_node(key, val, hv);
	if (!node)
		return (-1);
	node->next = *env;
	*env = node;
	return (0);
}
