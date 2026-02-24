/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2026/02/24 03:33:39 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	process_all(t_command *cmd, t_map *env, t_exec *exec)
{
	if (!cmd || !env)
		return ;
	init_exec(exec, cmd);
	if (!check_here_doc(cmd, env, exec))
		return ;
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
	env = create_env(environment);
	init_exec(&exec, NULL);
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
		process_all(cmd, env, &exec);
	}
	printf("Exiting minishell!\n");
	ft_exit(env, cmd, &exec, ft_atoi(env->get(env, "?")));
}
