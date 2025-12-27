/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:47:21 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/27 17:47:25 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(char *path, t_map *env)
{
	char	*home;

	home = env->get(env, "HOME");
	if (home)
	{
		if (chdir(home) == -1)
			return (print_error(CD_ERROR, path), 1);
	}
	else
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
	return (0);
}

static int	process_cd(char *path, t_map *env, char *old_pwd)
{
	if (!path || (!ft_strcmp(path, "~")))
		return (cd_home(path, env));
	if (!ft_strcmp(path, "-"))
	{
		if (old_pwd)
		{
			if (chdir(old_pwd) == -1)
				return (print_error(CD_ERROR, path), 1);
			else
				return (printf("%s\n", env->get(env, "OLDPWD")), 0);
		}
		else
			return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), 1);
	}
	if (path[0] == '~' && path[1] == '/')
	{
		cd_home(path, env);
		if (chdir(path + 2) == -1)
			return (print_error(CD_ERROR, path), 1);
		return (0);
	}
	if (chdir(path) == -1)
		return (print_error(CD_ERROR, path), 1);
	return (0);
}

int	built_in_cd(char **args, t_map *env)
{
	char	*pwd;
	char	*old_pwd;
	char	*path;
	int 	exit_code;

	if (ft_array_len(args) > 2)
		return (printf("bash: cd: too many arguments\n"), 1);
	path = args[1];
	pwd = getcwd(NULL, 0);
	old_pwd = env->get(env, "PWD");
	exit_code = process_cd(path, env, old_pwd);
	if (pwd && old_pwd)
	{
		env->put(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd), true);
		env->put(env, ft_strdup("PWD"), ft_strdup(pwd), true);
		free(pwd);
	}
	return (exit_code);
}
