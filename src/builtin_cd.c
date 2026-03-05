/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_shell *sh)
{
	char	*path;

	path = env_get(sh->env, "HOME");
	if (!path)
	{
		print_error("cd", NULL, "HOME not set");
		return (NULL);
	}
	return (path);
}

static char	*get_oldpwd_path(t_shell *sh)
{
	char	*path;

	path = env_get(sh->env, "OLDPWD");
	if (!path)
	{
		print_error("cd", NULL, "OLDPWD not set");
		return (NULL);
	}
	printf("%s\n", path);
	return (path);
}

static char	*get_cd_path(t_cmd *cmd, t_shell *sh)
{
	if (cmd->arg_count == 1)
		return (get_home_path(sh));
	if (ft_strcmp(cmd->args[1], "-") == 0)
		return (get_oldpwd_path(sh));
	return (cmd->args[1]);
}

static void	update_env_pwd(t_shell *sh, char *old, char *new_p)
{
	if (old)
		env_set(&sh->env, "OLDPWD", old, 1);
	if (new_p)
		env_set(&sh->env, "PWD", new_p, 1);
	free(old);
	free(new_p);
}

int	builtin_cd(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (cmd->arg_count > 2)
	{
		print_error("cd", NULL, "too many arguments");
		return (1);
	}
	path = get_cd_path(cmd, sh);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		print_error("cd", path, strerror(errno));
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	update_env_pwd(sh, old_pwd, new_pwd);
	return (0);
}
