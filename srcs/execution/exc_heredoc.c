#include "minishell.h"
bool expand_here_doc(char *line, t_map *env)
{
	char	*expanded;

	expanded = expand_word(ft_strdup(line), env, 0, 0);
	if (!expanded)
		return (false);
	// free(line);
	line = expanded;
	return (true);
}

static void	here_child(t_command *cmd, t_map *env, t_exec *exec)
{
	char	*limiter;
	char	*line;
	bool	expand_vars;
	int 	fd;
	
	fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (ft_exit(env, cmd, exec, 1));
	limiter = clean_limiter(cmd->infile->filename, &expand_vars);
	if (!limiter)
		return (ft_exit(env, cmd, exec, 1));
	handle_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || g_sig == SIGINT)
			(free(line), free(limiter), ft_close(&fd), ft_exit(env, cmd, exec, 130));
		if ((!ft_strcmp(line, limiter)) || (expand_vars && !expand_here_doc(line, env)))
			break ;
		(ft_dprintf(fd, "%s\n", line), free(line));
		line = NULL;
	}
	(free(line), free(limiter), ft_close(&fd), ft_exit(env, cmd, exec, 0));
}

static int	exec_here_doc(t_command *cmd, t_map *env, t_exec *exec)
{
	pid_t	pid;
	int		fd;
	int		status;
	int 	exit_code;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
		here_child(cmd, env, exec);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		exit_code = 128 + WTERMSIG(status);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	env->put(env, ft_strdup("?"), ft_itoa(exit_code), false);
	signal(SIGINT, sigint_handler);
	fd = open("/tmp/here_temp", O_RDONLY);
	unlink("/tmp/here_temp");
	return (fd);
}

bool	check_here_doc(t_command *cmd, t_map *env, t_exec *exec)
{
	t_command	*head;
	t_redirect	*temp;

	head = cmd;
	while (cmd)
	{
		temp = cmd->infile;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				temp->fd = exec_here_doc(cmd, env, exec);
				if (temp->fd < 0)
					return (false);
			}
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	cmd = head;
	return (true);
}
