#include "minishell.h"

void	clear_matriz(char **matriz)
{
	size_t	i;

	if (!matriz)
		return ;
	i = 0;
	while (matriz[i])
		free(matriz[i++]);
	free(matriz);
	matriz = NULL;
}

void	free_grid(char **grid)
{
	size_t	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

void clear_exec(t_exec *exec)
{
	if (!exec)
		return ;
	ft_close(&exec->in);
	ft_close(&exec->out);
	ft_close(&exec->temp_in);
	ft_close(&exec->temp_out);
	ft_close(&exec->fds[0]);
	ft_close(&exec->fds[1]);
	exec = NULL;
}

void list_clear_redir(t_redirect *head)
{
	t_redirect *next;

	if (!head)
		return ;
	while(head)
	{
		next = head->next;
		ft_close(&head->fd);
		if (head->filename)
			free(head->filename);
		free(head);
		head = next;
	}
	head = NULL;
}

void free_all(t_command *commands, t_exec *exec)
{
	t_command			*next;

	if (!commands)
		return ;
	while (commands->prev)
		commands = commands->prev;
	while (commands)
	{
		next = commands->next;
		list_clear_redir(commands->infile);
		list_clear_redir(commands->outfile);
		free(commands->path);
		clear_matriz(commands->args);
		clear_matriz(commands->cmd);
		free(commands);
		commands = next;
	}
	clear_exec(exec);
	commands = NULL;
}

