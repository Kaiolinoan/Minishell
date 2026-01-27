#include "minishell.h"

static bool	has_single_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

static char	*clean_limiter(char *raw, bool *expand_vars)
{
	char	*limiter;

	*expand_vars = !has_single_quotes(raw);
	limiter = remove_quotes(raw);
	return (limiter);
}

static void	here_child(t_command *cmd, t_map *env, t_exec *exec)
{
	char	*limiter;
	char	*line;
	char	*expanded;
	int		fd;
	bool	expand_vars;

	limiter = clean_limiter(cmd->infile->filename, &expand_vars);
	if (!limiter)
		return (ft_exit(env, cmd, exec, 1));
	fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (free(limiter), ft_exit(env, cmd, exec, 1));
	line = NULL;
	signal(SIGINT, heredoc_sigint);
	while (1)
	{
		rl_catch_signals = 0; 
		line = readline("> ");
		if (g_sig == SIGINT)
			ft_exit(env, cmd, exec, 130);
		if (!line)
		{
			free(limiter);
			ft_close(&fd);
			ft_exit(env, cmd, exec, 0);
		}
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& (line[ft_strlen(limiter)] == '\0'))
		{
			free(line);
			break ;
		}
		if (expand_vars)
		{
			expanded = expand_word(ft_strdup(line), env, 0, 0);
			if (!expanded)
			{
				free(limiter);
				return (ft_close(&fd), free(line), ft_exit(env, cmd, exec, 1));
			}
			free(line);
			line = expanded;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(limiter);
	ft_close(&fd);
	ft_exit(env, cmd, exec, 0);
}

static int	exec_here_doc(t_command *cmd, t_map *env, t_exec *exec)
{
	int		fd;
	struct sigaction sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	// signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;

	here_child(cmd, env, exec);
	// sigaction(SIGINT, &sa, NULL);

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
