/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/25 19:47:00 by klino-an         ###   ########.fr       */
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
			return (printf("Saindo do minishell!\n"), exit(0), -1);
		if (*str)
			add_history(str);
		exec_all(parse_main(str, NULL, env), env);
	}
	env->destroy(env);
}
//VERIFICAR SE IREMOS MANTER AS VARIAVEIS!
