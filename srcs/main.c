/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/15 13:06:46 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

void process_all(t_command *cmd, t_map *env, t_exec *exec)
{
	if (!cmd || !env)
		return ;
	init_exec(exec, cmd);
	if (!check_here_doc(cmd, env, exec))
		return (ft_exit(env, cmd, exec, 999));// checar isso aqui
	exec_all(cmd, env, exec);
}

int	main(int argc, char **argv, char **environment)
{
	char		*str;
	t_map		*env;
	t_command	*cmd;
	t_exec		exec;


	(void)argv;
	if (argc > 1)
		return (0);
	cmd = NULL;
	env = new_map();
	create_env(env, environment);
	while (1)
	{
		signals_init();
		str = readline("minishell> ");
		if (!str)
			break ;
		if (*str)
			add_history(str);
		free_all(cmd, &exec);
		cmd = parse_main(str, env, &exec);
		print_nodes_after_input(cmd);
		process_all(cmd, env, &exec);
	}
	printf("Saindo do minishell!\n");
	ft_exit(env, cmd, &exec, 0);
}
