/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/15 13:54:45 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

g_exit_code = 0;

int	main(int argc, char **argv, char **environment)
{
	char		*str;
	t_map		*env;
	t_command	*commands;
	char		**arg;

	(void)argc;
	(void)argv;
	env = new_map();
	create_env(env, environment);
	arg = NULL;
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			return (printf("Saindo do minishell!\n"), -1); //aqui da leak
		if (str && *str)
		{
			arg = ft_split(str, ' ');
			commands = new_command(arg);
			add_history(str);
			if (!is_built_in(str, env, commands))
				process_input(str, env, environment);
		}
		free(commands);
		clear_matriz(arg);
		free(str);
	}
	env->destroy(env);
}
//VERIFICAR SE IREMOS MANTER AS VARIAVEIS!
