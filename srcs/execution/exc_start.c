/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/09 12:51:27 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(t_map *env, t_command *commands)
{
	char *str;
	int exit_code;

	str = commands->args[0];
	exit_code = -1;
	if (!ft_strcmp(str, "env"))
		exit_code = env->print(env);
	if (!ft_strcmp(str, "pwd"))
		exit_code = built_in_pwd(env);
	if (!ft_strcmp(str, "echo"))
		exit_code = built_in_echo(commands);
	if (!ft_strcmp(str, "unset"))
		exit_code = built_in_unset(commands, env);
	if (!ft_strcmp(str, "export"))
		exit_code = built_in_export(commands, env);
	if (!ft_strcmp(str, "cd"))
		exit_code = built_in_cd(commands->args, env);
	if (!ft_strcmp(str, "exit"))
		exit_code = built_in_exit(commands, env);
	return (exit_code);
}
//exit nao esta saindo

void test_out(t_command *commands, char *filename, t_type type)
{
	t_redirect *out;

	if (!commands)
		return ;
	out = malloc(sizeof(t_redirect));
	if (!out)
		return ;
	out->filename = filename;
	out->type = type;
	out->next = NULL;
	out->fd = -1;
	commands->outfile = out;
}

void test_in(t_command *commands, char *filename, t_type type)
{
	t_redirect *in;

	if (!commands)
		return ;
	in = malloc(sizeof(t_redirect));
	if (!in)
		return ;
	in->filename = filename;
	in->type = type;
	in->next = NULL;
	in->fd = -1;
	commands->infile = in;
}
void fill_len(t_command *cmd)
{
	t_command *temp;
	size_t		len;

	len = list_len_command(cmd);
	temp = cmd;
	while (temp)
	{
		temp->exec->len = len;
		temp = temp->next;
	}
}

void exec_all(t_command *head, t_map *env)
{
	t_command	*cmd;
	t_exec		exec;

	cmd = head;
	// test_in(cmd, "a", HEREDOC);
	exec.in = dup(STDIN_FILENO);
	while (cmd)
	{
		exec.out = dup(STDOUT_FILENO);
		if (cmd->next)
			if (pipe(exec.fds) != -1)
				exec.out = change_fd(exec.out, exec.fds[1]);
		check_redir(cmd->infile, cmd->outfile, &exec.in, &exec.out);
		handle_command(env, cmd, &exec);
		exec.in = change_fd(exec.in, exec.fds[0]);
		cmd = cmd->next;
	}
}

//set follow-fork-mode child

