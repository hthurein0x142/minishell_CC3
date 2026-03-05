/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new_node(const char *key, const char *val, int hv)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = NULL;
	if (val)
		node->value = ft_strdup(val);
	node->has_value = hv;
	node->next = NULL;
	return (node);
}

static t_env	*make_node_from_entry(char *entry)
{
	char	*eq;
	t_env	*node;

	eq = strchr(entry, '=');
	if (eq)
	{
		*eq = '\0';
		node = env_new_node(entry, eq + 1, 1);
		*eq = '=';
	}
	else
		node = env_new_node(entry, NULL, 0);
	return (node);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = make_node_from_entry(envp[i]);
		if (node)
		{
			node->next = head;
			head = node;
		}
		i++;
	}
	return (head);
}

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0 && env->has_value)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
