/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/20 12:29:09 by klino-an         ###   ########.fr       */
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
		exit_code = env->print(env, commands);
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
	if (exit_code != -1)
		env->put(env, ft_strdup("?"), ft_itoa(exit_code), false);
	return (exit_code);
}
static int get_exit_status(int status, t_map *env)
{
	int			exit_code;

	exit_code = ft_atoi(env->get(env, "?"));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		   	write(2, "\n", 1);
		exit_code = 128 + WTERMSIG(status);
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code); 
}

static void	wait_all(t_command *cmd, t_map *env, t_exec *exec)
{
	t_command	*temp;
	int			status;
	int			exit_code;
	int			last_pid;

	(void)exec;
	temp = cmd;
	while (cmd->next)
		cmd = cmd->next;
	last_pid = cmd->pid;
	exit_code = ft_atoi(env->get(env, "?"));
	while (temp)
	{
		if (temp->pid == -1)
			if (cmd == temp)
				exit_code = exec->fake_status;
		if (waitpid(temp->pid, &status, 0) > 0)
			if (last_pid == temp->pid)
				exit_code =  get_exit_status(status, env);
		temp = temp->next;
	}
	env->put(env, ft_strdup("?"), ft_itoa(exit_code), false);
}

static void	redir_failure(t_command **cmd, t_exec **exec)
{
	(*cmd)->pid = -1;
	(*exec)->fake_status = 1;
	ft_close(&(*exec)->fds[1]);
	(*exec)->in = change_fd((*exec)->in, (*exec)->fds[0]);
	(*cmd) = (*cmd)->next;
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
		if (check_redir(cmd->infile, cmd->outfile, &exec->in, &exec->out) == -1)
		{
			redir_failure(&cmd, &exec);
			continue ;
		}
		if (cmd->args[0] && cmd->args[0][0])
			handle_command(env, cmd, exec);
		exec->in = change_fd(exec->in, exec->fds[0]);
		cmd = cmd->next;
	}
	cmd = head;
	wait_all(cmd, env, exec);
}

// set follow-fork-mode child
