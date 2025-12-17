/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/17 17:33:48 by klino-an         ###   ########.fr       */
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
static int check_error_msg(t_command *cmd)
{
	if (errno == ENOENT)
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
void cmd_not_found(t_command *cmd, t_map *env, int in, int out)
{
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_close(&in);
	ft_close(&out);
	ft_exit(env, cmd, 127);
}

void exec_failure(t_map *env, t_command *cmd, int in, int out)
{
	int exit_code;

	exit_code = check_error_msg(cmd);
	ft_close(&in);
	ft_close(&out);
	ft_exit(env, cmd, exit_code);
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
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		if (!cmd->path && ft_strchr(cmd->args[0], '/') == NULL)
			(clear_matriz(environment), cmd_not_found(cmd, env, in , out));
		if (ft_strchr(cmd->args[0], '/'))
			execve(cmd->args[0], cmd->args, environment);
		else 
			execve(cmd->path, cmd->args, environment);
		clear_matriz(environment);
		exec_failure(env, cmd, in, out);
	}
	wait_all(cmd);
	ft_close(&out);
	ft_close(&in);
	// ft_close(&cmd->infile->fd);
	clear_matriz(environment);
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
		return (built_in_exit(cmd, env));
	in = dup(STDIN_FILENO);
	while (cmd)
	{
		out = dup(STDOUT_FILENO);
		if (cmd->next && pipe(fds) != -1)
			out = change_fd(out, fds[1]);
		check_redir(cmd->infile, cmd->outfile, &in, &out);
		single_command(env, cmd, in, out);
		in = change_fd(in, fds[0]);
		cmd = cmd->next;
	}
}

