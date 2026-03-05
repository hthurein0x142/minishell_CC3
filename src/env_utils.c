/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->has_value)
			n++;
		env = env->next;
	}
	return (n);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;
	int		n;

	n = env_size(env);
	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->has_value)
		{
			if (env->value)
				arr[i] = ft_strjoin3(env->key, "=", env->value);
			else
				arr[i] = ft_strjoin3(env->key, "=", "");
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	env_free_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	env_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
