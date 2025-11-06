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

static void	only_export(t_map *env)
{
	char **matriz;
	size_t i;
	size_t j;

	matriz = env->to_string(env);
	if (!matriz)
		return ;
	i = 0;
	sort_str(matriz);
	while (matriz[i])
	{
		j = 0;
		printf("declare -x ");
		while (matriz[i][j] != '=')
			printf("%c", matriz[i][j++]);
		printf("=\"");
		while (matriz[i][++j])
			printf("%c", matriz[i][j]);
		printf("\"\n");
		i++;
	}
	clear_matriz(matriz);
}

static bool	ft_check_var_name(char *str)
{
	size_t i;

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
void	process_export_args(t_command *commands, t_map *env, int i)
{
	char **args;

	if (ft_strchr(commands->command[i], '='))
	{
		args = ft_split_env(commands->command[i]);
		if (!args)
			return ;
		if (args[0] && args[1])
		{
			if (ft_check_var_name(args[0]))
				env->put(env, args[0], args[1], true);
			else
				printf("bash: export: `%s': not a valid identifier\n",
					args[0]);
		}
		else
		{
			if (args[0])
				free(args[0]);
			if (args[1])
				free(args[1]);
		}
	}
	else
		env->set_var_as_exported(env, commands->command[i]); //rever todos os comportamentos do export depois para verificar isso
}

void	built_in_export(t_command *commands, t_map *env)
{
	size_t i;

	i = 1;
	if (commands->command[0] && (!commands->command[1]))
	{
		only_export(env);
		return ;
	}
	while (commands->command[i])
		process_export_args(commands, env, i++);
}

/*CODIGO QUE ESTAVA NO EXPORT PARA TESTAR VARIAVEIS:*/
// char *key = ft_strdup("VAR");
// char *value = ft_strdup("20");
// var = new_var(key, value, false, false);
// create_variable(env, commands, var);
