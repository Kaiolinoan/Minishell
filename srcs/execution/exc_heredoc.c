/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 05:09:11 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 05:51:13 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_child(t_command *cmd, t_map *env,
	t_exec *exec, t_redirect *redir)
{
	char	*limiter;
	bool	expand_vars;
	int		fd;

	fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (ft_exit(env, cmd, exec, 1));
	limiter = clean_limiter(redir, &expand_vars);
	if (!limiter)
		return (ft_close(&fd), ft_exit(env, cmd, exec, 1));
	handle_heredoc_signals();
	if (!heredoc_loop(fd, limiter, expand_vars, env))
		return (free(limiter), ft_close(&fd),
			ft_exit(env, cmd, exec, 130));
	free(limiter);
	ft_close(&fd);
	ft_exit(env, cmd, exec, 0);
}

static int	exec_here_doc(t_command *cmd, t_map *env,
	t_exec *exec, t_redirect *redir)
{
	pid_t	pid;
	int		fd;
	int		status;
	int		exit_code;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
		here_child(cmd, env, exec, redir);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		exit_code = 128 + WTERMSIG(status);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	put_exit_code_in_env(env, exit_code);
	signal(SIGINT, sigint_handler);
	fd = open("/tmp/here_temp", O_RDONLY);
	unlink("/tmp/here_temp");
	return (fd);
}

static bool	heredoc_process_redirects(t_command *cmd,
	t_map *env, t_exec *exec)
{
	t_redirect	*temp;

	temp = cmd->infile;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			temp->fd = exec_here_doc(cmd, env, exec, temp);
			if (temp->fd < 0)
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}

bool	check_here_doc(t_command *cmd, t_map *env, t_exec *exec)
{
	while (cmd)
	{
		if (!heredoc_process_redirects(cmd, env, exec))
			return (false);
		cmd = cmd->next;
	}
	return (true);
}
