/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/13 12:05:23 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environment)
{
	char		*str;
	t_map		*env;
	t_command	*commands;

	(void)argc;
	(void)argv;
	env = new_map();
	create_env(env, environment);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
		{
			printf("Saindo do minishell!\n");
			free(str);
			break ;
		}
		if (str && *str)
		{
			commands = new_command(ft_split(str, ' '));
			add_history(str);
			if (!is_built_in(str, env, commands))
				process_input(str, env, environment);
		}
		free(str);
	}
	env->destroy(env);
}
//VERIFICAR SE IREMOS MANTER AS VARIAVEIS!

//CD .. da seg fault
