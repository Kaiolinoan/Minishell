/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/13 11:47:07 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(char *str, t_map *env, t_command *commands)
{
	if (!ft_strncmp(str, "env", 3) && ft_strlen(str) == ft_strlen("env"))
	{
		env->print(env);
		return (true);
	}
	if (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == ft_strlen("pwd"))
	{
		built_in_pwd(env);
		return (true);
	}
	if (!ft_strncmp(str, "echo", 4))
	{
		built_in_echo(commands);
		return (true);
	}
	if (!ft_strncmp(str, "unset", 5))
	{
		built_in_unset(commands, env);
		return (true);
	}
	if (!ft_strncmp(str, "export", 6))
	{
		built_in_export(commands, env);
		return (true);
	}
	if (!ft_strncmp(str, "cd", 2))
	{
		// if (commands->command[2])
        // 	return (printf("bash: cd: too many arguments\n"), true);
		built_in_cd(commands->command[1], env);
		return (true);
	}
	if (!ft_strncmp(str, "exit", 4) && ft_strlen(str) == ft_strlen2("exit"))
	{
		built_in_exit(commands, env, str);
		return (true);
	}
	return (false);
}

void	process_input(char *str, t_map *env, char **environment)
{
	int		pid;
	char	*path;
	char	**input;

	pid = fork();
	if (!pid)
	{
		input = ft_split(str, ' ');
		if (!input)
		{
			free(str);
			env->destroy(env);
			return ;
		}
		path = get_path(env, str);
		if (!path)
		{
			printf("aqui tem que ser um command not found!\n");
			clear_matriz(input);
			return ;
		}
		execve(path, input, environment);
		clear_matriz(input);
		free(path);
		printf("falha ao executar execve\n");
	}
	wait(NULL);
}
