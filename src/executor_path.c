/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_direct_path(char *cmd)
{
	return (cmd[0] == '/' || cmd[0] == '.'
		|| (cmd[0] && cmd[1] && cmd[0] == '.' && cmd[1] == '/'));
}

static char	*try_path_dirs(char *cmd, char *path_val)
{
	char	**dirs;
	char	*full;
	int		i;

	dirs = ft_split(path_val, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full = ft_strjoin3(dirs[i], "/", cmd);
		if (full && access(full, F_OK) == 0)
		{
			env_free_array(dirs);
			if (access(full, X_OK) == 0)
				return (full);
			free(full);
			return (NULL);
		}
		free(full);
		i++;
	}
	env_free_array(dirs);
	return (NULL);
}

char	*resolve_path(char *cmd, t_shell *sh)
{
	char		*path_val;
	struct stat	sb;

	if (!cmd || !cmd[0])
		return (NULL);
	if (is_direct_path(cmd))
	{
		if (stat(cmd, &sb) == -1)
			return (NULL);
		if (S_ISDIR(sb.st_mode))
		{
			print_error(cmd, NULL, "Is a directory");
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_val = env_get(sh->env, "PATH");
	if (!path_val || !path_val[0])
		return (NULL);
	return (try_path_dirs(cmd, path_val));
}
