/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/13 11:21:02 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(t_map *env, t_command *commands, t_exec *exec)
{
	char	*str;
	int		exit_code;

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
		exit_code = built_in_exit(commands, env, exec);
	return (exit_code);
}
static int get_exit_status(int status)
{
	int			exit_code;

	exit_code = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		if (WTERMSIG(status) == SIGINT)
		   	write(2, "\n", 1);
		exit_code = 128 + WTERMSIG(status);
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code); 
}

static void	wait_all(t_command *cmd, t_map *env)
{
	t_command	*temp;
	int			status;
	int			exit_code;
	int			last_pid;

	temp = cmd;
	while (cmd->next)
		cmd = cmd->next;
	last_pid = cmd->pid;
	exit_code = 0;
	while (temp)
	{
		if (waitpid(temp->pid, &status, 0) > 0)
			if (last_pid == temp->pid)
				get_exit_status(status);
		temp = temp->next;
	}
	env->put(env, ft_strdup("?"), ft_itoa(exit_code), true);// alterar para false dps que tiver a expansao
}

void	exec_all(t_command *head, t_map *env, t_exec *exec)
{
	t_command	*cmd;

	cmd = head;
	exec->in = dup(STDIN_FILENO);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd)
	{
		exec->out = dup(STDOUT_FILENO);
		if (cmd->next)
			if (pipe(exec->fds) != -1)
				exec->out = change_fd(exec->out, exec->fds[1]);
		check_redir(cmd->infile, cmd->outfile, &exec->in, &exec->out);
		handle_command(env, cmd, exec);
		exec->in = change_fd(exec->in, exec->fds[0]);
		cmd = cmd->next;
	}
	cmd = head;
	wait_all(cmd, env);
}

// set follow-fork-mode child
