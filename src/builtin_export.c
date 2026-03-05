/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_sorted(t_shell *sh)
{
	t_env	**visited;
	int		count;
	int		v_count;
	t_env	*min;

	count = env_count(sh->env);
	visited = malloc(sizeof(t_env *) * count);
	if (!visited)
		return ;
	v_count = 0;
	while (v_count < count)
	{
		min = env_find_min(sh->env, visited, v_count);
		if (min)
		{
			print_one_export(min);
			visited[v_count] = min;
		}
		v_count++;
	}
	free(visited);
}

static int	export_with_value(char *arg, char *eq, t_shell *sh)
{
	char	*key;

	key = ft_strndup(arg, eq - arg);
	if (!is_valid_identifier(key))
	{
		print_error("export", arg, "not a valid identifier");
		free(key);
		return (1);
	}
	env_set(&sh->env, key, eq + 1, 1);
	free(key);
	return (0);
}

static int	export_one(char *arg, t_shell *sh)
{
	char	*eq;

	eq = strchr(arg, '=');
	if (eq)
		return (export_with_value(arg, eq, sh));
	if (!is_valid_identifier(arg))
	{
		print_error("export", arg, "not a valid identifier");
		return (1);
	}
	env_set(&sh->env, arg, NULL, 0);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *sh)
{
	int	i;
	int	ret;

	if (cmd->arg_count == 1)
	{
		print_export_sorted(sh);
		return (0);
	}
	ret = 0;
	i = 1;
	while (i < cmd->arg_count)
	{
		if (export_one(cmd->args[i], sh) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
