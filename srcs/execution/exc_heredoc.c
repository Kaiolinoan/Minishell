
#include "minishell.h"

static void here_child(char *limiter, t_command *cmd, t_map *env)
{
	char	*line;
    int     fd;

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
    ft_exit(env, cmd, 0);
}

int exec_here_doc(t_command *cmd, t_map *env)
{
    pid_t   pid;
    int     fd;
    
    pid = fork();
    if (pid < 0)
        return (-1);
    if (!pid)
        here_child(cmd->infile->filename, cmd, env);
    wait(NULL);
    fd = open("/tmp/here_temp", O_RDONLY);
    unlink("/tmp/here_temp");
	return (fd);
}

bool check_here_doc(t_command *cmd, t_map *env)
{
	t_command	*head;
	head = cmd;
	while (cmd)
	{
		if (cmd->infile && cmd->infile->type == HEREDOC)
		{
			cmd->infile->fd = exec_here_doc(cmd, env);
			if (cmd->infile->fd < 0)
				return (false);
		}
		cmd = cmd->next;
	}
	cmd = head;
	return (true);
}