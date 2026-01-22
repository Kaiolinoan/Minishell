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

	signal(SIGINT, heredoc_sigint);
	limiter = clean_limiter(cmd->infile->filename, &expand_vars);
	if (!limiter)
		return (ft_exit(env, &cmd, exec, 1));
	fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (free(limiter), ft_exit(env, &cmd, exec, 1));
	line = NULL;
	while (1)
	{
		line = readline("> ");
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
				return (ft_close(&fd), free(line), ft_exit(env, &cmd, exec, 1));
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
	pid_t	pid;
	int		fd;
	int status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
		here_child(cmd, env, exec);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (unlink("/tmp/here_temp"), -2);
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
				print_inside_redir(temp);
			}
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	cmd = head;
	return (true);
}
