/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/25 20:15:36 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static bool	is_built_in(t_map *env, t_command *commands)
// {
// 	char *str;

// 	str = commands->args[0];
// 	if (!ft_strcmp(str, "env"))
// 		return (env->print(env), true);
// 	if (!ft_strcmp(str, "pwd"))
// 		return (built_in_pwd(env), true);
// 	if (!ft_strcmp(str, "echo"))
// 		return (built_in_echo(commands), true);
// 	if (!ft_strcmp(str, "unset"))
// 		return (built_in_unset(commands, env), true);
// 	if (!ft_strcmp(str, "export"))
// 		return (built_in_export(commands, env), true);
// 	if (!ft_strcmp(str, "cd"))
// 		return (built_in_cd(commands->args, env), true);
// 	if (!ft_strcmp(str, "exit"))
// 		return (built_in_exit(commands, env), true);
// 	return (false);
// }

void wait_all(t_command *cmd)
{
	while (cmd)
	{
		wait(NULL);
		cmd = cmd->next;
	}
}

static void	single_command(t_map *env, t_command *cmd, int in, int out)
{
	printf("cmd: %s in: %i out: %i\n", cmd->args[0], in , out);		

	cmd->pid = fork();
	if (cmd->pid < 0)
		printf("ERROR: fork()\n");
	else if (cmd->pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		execve(cmd->path, cmd->args, env->to_string(env));
		ft_putstr_fd("ERROR: execve()\n", 2);
		built_in_exit(cmd, env);
	}
	wait_all(cmd);
	close(in);
	close(out);
}

// void test_out(t_command *commands)
// {
// 	t_redirect *out;

// 	if (!commands)
// 		return ;
// 	out = malloc(sizeof(t_redirect));
// 	if (!out)
// 		return ;
// 	out->filename = "b";
// 	out->type = OUTPUT;
// 	commands->outfile = out;
// }

// void test_in(t_command *commands)
// {
// 	t_redirect *in;

// 	if (!commands)
// 		return ;
// 	in = malloc(sizeof(t_redirect));
// 	if (!in)
// 		return ;
// 	in->filename = "a";
// 	in->type = INPUT;
// 	commands->infile = in;
// }



void exec_all(t_command *head, t_map *env)
{
	t_command	*cmd;
	int			in;
	int			out;
	int			fds[2];

	if (!head || !env)
		return ;
	cmd = head;
	in = dup(STDIN_FILENO);
	while (cmd)
	{	
		out = dup(STDOUT_FILENO);
		if (cmd->next && pipe(fds) != -1)
			out = change_fd(out, fds[1]);
		// tratar das redirections
		single_command(env, cmd, in, out);
		in = change_fd(in, fds[0]);
		cmd = cmd->next;
	}		
	wait_all(head);
}

