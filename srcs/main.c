/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/19 11:56:56 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

int	main(int argc, char **argv, char **environment)
{
	char		*str;
	t_map		*env;

	(void)argc;
	(void)argv;
	env = new_map();
	create_env(env, environment);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			return (printf("Saindo do minishell!\n"), -1);
		if (*str)
			add_history(str);
		handle_input(str, env);
	}
	env->destroy(env);
}

// int	main(int argc, char **argv, char **environment)
// {
// 	char		*str;
// 	t_map		*env;
// 	t_command	*commands;

// 	(void)argc;
// 	(void)argv;
// 	env = new_map();
// 	create_env(env, environment);
// 	while (1)
// 	{
// 		str = readline("minishell> ");
// 		if (!str)
// 		{
// 			printf("Saindo do minishell!\n");
// 			break ;
// 		}
// 		if (*str)
// 			add_history(str);
// 		commands = parse_main(str, commands);
// 		if (!is_built_in(str, env, commands))
// 			process_input(str, env, environment);
// 	}
// 	free (str);
// 	env->destroy(env);
// }
//VERIFICAR SE IREMOS MANTER AS VARIAVEIS!
