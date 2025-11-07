/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:47:21 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/07 12:34:46 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(char *path, t_map *env)
{
	char	*home;

	home = env->get(env, "HOME");
	if (home)
	{
		if (chdir(home) == -1)
			print_error(CD_ERROR, path);
	}
	else
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
}

static void	process_cd(char *path, t_map *env, char *old_pwd)
{
	if (!path || (!ft_strcmp(path, "~")))
		return (cd_home(path, env));
	if (!ft_strcmp(path, "-"))
	{
		if (old_pwd)
		{
			if (chdir(old_pwd) == -1)
				print_error(CD_ERROR, path);
			else
				return ((void)printf("%s\n", env->get(env, "OLDPWD")));
		}
		else
			return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2));
	}
	if (path[0] == '~' && path[1] == '/')
	{
		cd_home(path, env);
		if (chdir(path + 2) == -1)
			return (print_error(CD_ERROR, path));
		return ;
	}
	if (chdir(path) == -1)
		print_error(CD_ERROR, path);
}

int	built_in_cd(char *path, t_map *env)
{
	char	*pwd;
	char	*old_pwd;

	process_cd(path, env, env->get(env, "OLDPWD"));
	pwd = getcwd(NULL, 0);
	old_pwd = env->get(env, "PWD");
	if (pwd && old_pwd)
	{
		env->put(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd), true);
		env->put(env, ft_strdup("PWD"), ft_strdup(pwd), true);
		free(pwd);
	}
	return (0);
}
