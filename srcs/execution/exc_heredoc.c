#include "minishell.h"

static void	here_child(t_command *cmd, t_map *env, t_exec *exec)
{
	char	*limiter;
	char	*line;
	int		fd;

	limiter = cmd->infile->filename;
	fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			(ft_close(&fd), exit(0));
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& (line[ft_strlen(limiter)] == '\0'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	ft_close(&fd);
	ft_exit(env, cmd, exec, 0);
}

static int	exec_here_doc(t_command *cmd, t_map *env, t_exec *exec)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
		here_child(cmd, env, exec);
	wait(NULL);
	fd = open("/tmp/here_temp", O_RDONLY);
	unlink("/tmp/here_temp");
	return (fd);
}

bool	check_here_doc(t_command *cmd, t_map *env, t_exec *exec)
{
	t_command	*head;
	t_redirect	*temp;

	head = cmd;
	temp = head->infile;
	while (cmd)
	{
		while (cmd->infile)
		{
			if (cmd->infile->type == HEREDOC)
			{
				cmd->infile->fd = exec_here_doc(cmd, env, exec);
				if (cmd->infile->fd < 0)
					return (false);
			}
			cmd->infile = cmd->infile->next;
		}
		cmd = cmd->next;
	}
	cmd = head;
	cmd->infile = temp;
	return (true);
}
