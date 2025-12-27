/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/27 18:28:10 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_built_in(t_map *env, t_command *commands)
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
static int check_error_msg(t_command *cmd)
{
	if (!cmd->path[0])
		return (ft_putstr_fd(*cmd->args, 2), ft_putstr_fd(": command not found\n", 2), 127);
	else if (errno == ENOENT)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	else if (errno ==  EACCES)
	{
		DIR *d;

		d = opendir(cmd->args[0]);
		if (d)
		{
			(closedir(d), ft_putstr_fd(cmd->args[0], 2));
			ft_putstr_fd(": Is a directory\n", 2);
			return (126);
		}
		else 
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (126);
		}
	}
	return (127);
} 

void exec_failure(t_map *env, t_command *cmd, int in, int out)
{
	int exit_code;

	exit_code = check_error_msg(cmd);
	ft_close(&in);
	ft_close(&out);
	ft_exit(env, cmd, exit_code);
}

void finish_process(int *in, int *out, t_command *cmd, char **matriz)
{
	(void) cmd;
	ft_close(out);
	ft_close(in);
	// ft_close(&cmd->infile->fd);
	clear_matriz(matriz);
}

static void	single_command(t_map *env, t_command *cmd, int in, int out)
{
	char	**environment;

	environment = env->to_string(env);
	cmd->pid = fork();
	if (cmd->pid < 0)
		printf("ERROR: fork()\n");
	else if (cmd->pid == 0)
	{
		// ft_printf("path:%s\ncmd: %s\n", cmd->path, cmd->args[0]);
		// ft_printf("in:%d\nout: %d\n", in, out);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		if (ft_strchr(cmd->args[0], '/'))
			execve(cmd->args[0], cmd->args, environment);
		else
		{
			if (is_built_in(env, cmd) == -1)
				execve(cmd->path, cmd->args, environment);
			finish_process(&in, &out, cmd, environment);
			return (ft_exit(env, cmd, 0));
		}
		clear_matriz(environment);
		exec_failure(env, cmd, in, out);
	}
	wait_all(cmd);
	finish_process(&in, &out, cmd, environment);
}

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

void exec_all(t_command *head, t_map *env)
{
	t_command	*cmd;
	int			in;
	int			out;
	int			fds[2];

	if (!head || !env)
		return ;
	cmd = head;
	// test_in(cmd, "a", HEREDOC);	
	if (!check_here_doc(cmd, env))
		return ((void)built_in_exit(cmd, env));
	in = dup(STDIN_FILENO);
	while (cmd)
	{
		out = dup(STDOUT_FILENO);
		if (cmd->next)
		{
			if (pipe(fds) != -1)
				out = change_fd(out, fds[1]);
		}
		check_redir(cmd->infile, cmd->outfile, &in, &out);
		single_command(env, cmd, in, out);
		in = change_fd(in, fds[0]);
		cmd = cmd->next;
	}
}


