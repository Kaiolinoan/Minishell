/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:47:21 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/13 14:50:11 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str, char *filename)
{
	write(2, str, ft_strlen(str));
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 2);
}

static int	cd_home(char *path, t_map *env)
{
	char	*home;

	home = env->get(env, "HOME");
	if (home)
	{
		if (chdir(home) == -1)
			return (print_error(BASH_CD, path), 1);
	}
	else
		return (ft_dprintf(2, "bash: cd: HOME not set\n"), 1);
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
				return (print_error(BASH_CD, path), 1);
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
			return (print_error(BASH_CD, path), 1);
		return (0);
	}
	if (chdir(path) == -1)
		return (print_error(BASH_CD, path), 1);
	return (0);
}

int	built_in_cd(char **args, t_map *env)
{
	char	*pwd;
	char	*old_pwd;
	char	*path;
	int 	exit_code;

	if (ft_array_len(args) > 2)
		return (ft_dprintf(2, "bash: cd: too many arguments\n"), 1);
	path = args[1];
	old_pwd = env->get(env, "PWD");
	exit_code = process_cd(path, env, env->get(env, "OLDPWD"));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_dprintf(2, CD_ERROR);
	if (pwd && old_pwd)
	{
		env->put(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd), true);
		env->put(env, ft_strdup("PWD"), ft_strdup(pwd), true);
	}
	return (free(pwd), exit_code);
}
