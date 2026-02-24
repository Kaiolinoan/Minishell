/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:47:21 by klino-an          #+#    #+#             */
/*   Updated: 2026/02/15 05:33:44 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(char *path, char *raw_path)
{
	char	*buffer;

	buffer = NULL;
	if (raw_path[0] == '/')
	{
		ft_dprintf(2, "bash: cd: %s: ", path);
		perror(NULL);
		return (1);
	}
	else
	{
		buffer = getcwd(NULL, 0);
		if (!buffer)
			return (ft_dprintf(2, CD_ERROR), 0);
		ft_dprintf(2, "bash: cd: %s: ", raw_path);
		perror(NULL);
		free(buffer);
	}
	return (1);
}

static int	cd_home(char *path, t_map *env)
{
	char	*home;

	home = env->get(env, "HOME");
	if (home)
	{
		if (chdir(home) == -1)
			return (print_error(path, NULL));
	}
	else
		return (ft_dprintf(2, "bash: cd: HOME not set\n"), 1);
	return (0);
}

static int	process_cd(char *path, t_map *env, char *old_pwd, char *raw_path)
{
	if (!path || (!ft_strcmp(path, "~")))
		return (cd_home(path, env));
	if (!ft_strcmp(path, "-"))
	{
		if (old_pwd)
		{
			if (chdir(old_pwd) == -1)
				return (print_error(path, raw_path));
			else
				return (ft_printf("%s\n", old_pwd), 0);
		}
		else
			return (ft_dprintf(2, "bash: cd: OLDPWD not set\n"), 1);
	}
	if (path[0] == '~' && path[1] == '/')
	{
		if (cd_home(path, env) == 1)
			return (1);
		if (chdir(path + 2) == -1)
			return (print_error(path, raw_path));
		return (0);
	}
	if (chdir(path) == -1)
		return (print_error(path, raw_path));
	return (0);
}

int	built_in_cd(char **args, t_map *env)
{
	char	*pwd;
	char	*old_pwd;
	char	*path;
	int		exit_code;

	if (ft_array_len(args) > 2)
		return (ft_dprintf(2, "bash: cd: too many arguments\n"), 1);
	path = process_cd_path(args[1], env);
	if (!path)
		return (free(path), 0);
	old_pwd = env->get(env, "PWD");
	exit_code = process_cd(path, env, env->get(env, "OLDPWD"), args[1]);
	free(path);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = process_cd_path(args[1], env);
	if (pwd && old_pwd)
	{
		env->put(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd), true);
		env->put(env, ft_strdup("PWD"), ft_strdup(pwd), true);
	}
	return (free(pwd), exit_code);
}
