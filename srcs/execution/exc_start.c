/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/05 11:31:17 by klino-an         ###   ########.fr       */
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

	if (!head || !env)
		return ;
	cmd = head;
	// test_in(cmd, "a", HEREDOC);
	fill_len(cmd);
	if (!check_here_doc(cmd, env))
		return ((void)built_in_exit(cmd, env));
	cmd->exec->in = dup(STDIN_FILENO);
	while (cmd)
	{
		cmd->exec->out = dup(STDOUT_FILENO);
		if (cmd->next)
			if (pipe(cmd->exec->fds) != -1)
				cmd->exec->out = change_fd(cmd->exec->out, cmd->exec->fds[1]);
		check_redir(cmd->infile, cmd->outfile, &cmd->exec->in, &cmd->exec->out);
		handle_command(env, cmd, cmd->exec->in, cmd->exec->out);
		cmd->exec->in = change_fd(cmd->exec->in, cmd->exec->fds[0]);
		cmd = cmd->next;
	}
	free_all(head);
}

//set follow-fork-mode child

