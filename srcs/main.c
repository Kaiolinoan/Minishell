/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/28 12:43:17 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

int	main(int argc, char **argv, char **environment)
{
	char		*str;
	t_map		*env;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	if (argc > 1)
		return (0);
	env = new_map();
	create_env(env, environment);
	cmd = NULL;
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		if (*str)
			add_history(str);
		cmd = parse_main(str, NULL, env);
		exec_all(cmd, env);
	}
	printf("Saindo do minishell!\n");
	ft_exit(env, cmd, 0);
}
//VERIFICAR SE IREMOS MANTER AS VARIAVEIS!
