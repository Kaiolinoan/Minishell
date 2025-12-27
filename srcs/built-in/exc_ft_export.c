/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:55:46 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/06 16:55:46 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_export(char **matriz, int i)
{
	int	j;

	j = 0;
	while (matriz[i][j] != '=')
		printf("%c", matriz[i][j++]);
	printf("=\"");
	while (matriz[i][++j])
		printf("%c", matriz[i][j]);
	printf("\"\n");
	i++;
}

static int	only_export(t_map *env)
{
	char	**matriz;
	size_t	i;

	matriz = env->to_string(env);
	if (!matriz)
		return (1);
	i = 0;
	sort_str(matriz);
	while (matriz[i])
	{
		printf("declare -x ");
		if (ft_strchr(matriz[i], '='))
			print_export(matriz, i);
		else
			printf("%s\n", matriz[i]);
		i++;
	}
	clear_matriz(matriz);
	return (0);
}

static bool	ft_check_var_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[0]) == 0)
			if (str[0] != '_')
				return (false);
		if (ft_isalnum(str[i]) == 0)
			if (str[i] != '_')
				return (false);
		i++;
	}
	return (true);
}

static int	process_export_args(t_command *commands, t_map *env, int i)
{
	char *name;
	char **args;
	bool flag;

	flag = false;
	name = NULL;
	if (ft_strchr(commands->args[i], '='))
	{
		args = ft_split_env(commands->args[i]);
		if (!*args[0])
			return (printf("bash: export: `%s': not a valid identifier\n",
				commands->args[i]), 1);
		name = args[0];
		flag = true;
	}
	else
		name = commands->args[i];
	if (!ft_check_var_name(name))
		return (printf("bash: export: `%s': not a valid identifier\n",
				commands->args[i]), 1);
	if (flag)
		env->put(env, name, args[1], true);
	else
		env->set_var_as_exported(env, commands->args[i]);
	return (0);
}

int	built_in_export(t_command *commands, t_map *env)
{
	size_t	i;
	int		exit_code;

	i = 1;
	if (commands->args[0] && (!commands->args[1]))
		return (only_export(env));
	while (commands->args[i])
		exit_code = process_export_args(commands, env, i++);
	return (exit_code);
}
