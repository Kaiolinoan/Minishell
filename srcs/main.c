/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/17 14:53:37 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

static void	process_all(t_command *cmd, t_map *env, t_exec *exec)
{
	if (!cmd || !env)
		return ;
	if (!check_here_doc(cmd, env, exec))
		return (ft_exit(env, cmd, exec, 999));// checar isso aqui
	exec_all(cmd, env, exec);
}

static void	initialize_exec(t_exec *exec)
{
	exec->in = -1;
	exec->out = -1;
	exec->fds[0] = -1;
	exec->fds[1] = -1;
	exec->len = 0;
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
	initialize_exec(&exec);
	while (1)
	{
		signals_init();
		str = readline("minishell> ");
		if (!str)
			break ;
		if (*str)
			add_history(str);
		cmd = parse_main(str, env, &exec);
		if (!cmd)
			continue ;
		print_nodes_after_input(cmd);
		process_all(cmd, env, &exec);
		free_all(cmd, &exec);
	}
	printf("Saindo do minishell!\n");
	ft_exit(env, cmd, &exec, 0);
}
//VERIFICAR SE IREMOS MANTER AS VARIAVEIS!
