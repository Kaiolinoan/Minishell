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
	char	**matriz;
	size_t	i;
	size_t	j;

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
// static bool check_var_sintax(char *str)
// {
// 	if (!ft_strchr(str, '='))
// 	{
// 		printf("bash: export: `%s': not a valid identifier\n",
// 				str);
// 		return (false);
// 	}
// 	return (true);
// }
// static void	process_export_args(t_command *commands, t_map *env, int i)
// {
// 	char	**args;

// 	if (check_var_sintax(commands->args[i]))
// 	{
// 		args = ft_split_env(commands->args[i]);
// 		if (!args)
// 			return ;
// 		if (args[0] && args[1])
// 		{
// 			// printf("args[0]: %s, ascii: %d\n", args[0], args[0][0]);
// 			// printf("args[1]: %s, ascii: %d\n", args[1], args[1][0]);	
// 			if (ft_check_var_name(args[0]) && args[0][0] != '\0')
// 				env->put(env, args[0], args[1], true);
// 			else
// 				printf("bash: export: `%s': not a valid identifier\n",
// 					args[0]);
// 		}
// 		else
// 		{
// 			if (args[0])
// 				free(args[0]);
// 			if (args[1])
// 				free(args[1]);
// 		}
// 	}
// 	else
// 		env->set_var_as_exported(env, commands->args[i]);
// }

static void	process_export_args(t_command *commands, t_map *env, int i)
{
	char *name;
	char **args;
	(void)env;
	name = NULL;
	if (ft_strchr(commands->args[i], '='))
	{
		args = ft_split_env(commands->args[i]);
		if (args[0] != NULL)
			name = args[0];
	}
	else
		name = commands->args[i];
	ft_printf("%s\n", name);
	if (!ft_check_var_name(name))
		printf("bash: export: `%s': not a valid identifier\n",
				name);
}

void	built_in_export(t_command *commands, t_map *env)
{
	size_t	i;

	i = 1;
	if (commands->args[0] && (!commands->args[1]))
		return (only_export(env));
	while (commands->args[i])
	{
		if (commands->args[i][0] != '\0')
			process_export_args(commands, env, i++);
	}
	
}

/*CODIGO QUE ESTAVA NO EXPORT PARA TESTAR VARIAVEIS:*/
/* char *key = ft_strdup("VAR");
char *value = ft_strdup("20");
var = new_var(key, value, false, false);
create_variable(env, commands, var);
 */