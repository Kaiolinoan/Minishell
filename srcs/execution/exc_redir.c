/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:42:23 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/09 17:40:06 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void here_child(char *limiter)
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
    exit(0);
}

int exec_here_doc(char *limiter)
{
    pid_t   pid;
    int     fd;
    
    pid = fork();
    if (pid < 0)
        return (-1);
    if (!pid)
        here_child(limiter);
    wait(NULL);
    fd = open("/tmp/here_temp", O_RDONLY);
    unlink("/tmp/here_temp");
	return (fd);
}

static int helper_input(t_redirect *input)
{
    int fd;
    
    if (!input)
		return  -1;
    fd = STDIN_FILENO;
	while (input)
    {
		if (input->type == INPUT)
		{
			fd = open(input->filename, O_RDONLY);
			if (fd < 0)
				return (ft_putstr_fd("ERROR: open()\n", 2), -1);
		}
		input = input->next;
	}
    return fd;
}

static int helper_output(t_redirect *output)
{
    int fd;
    if (!output)
		return (-1);
    fd = STDOUT_FILENO;
	while (output)
	{
		if (output->type == OUTPUT)
			fd = open(output->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (output->type == OUTPUT_APPEND)
			fd = open(output->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (ft_putstr_fd("ERROR: open()\n", 2), -1);
		output = output->next;
	}
    return (fd);
}

void check_redir(t_redirect *input, t_redirect *output, int *in, int *out)
{
	if (!input && !output)
		return ;
        
    if (input)
    {
        printf("%d\n", *in);
        if (input->type == INPUT)
            *in = change_fd(*in, helper_input(input));
        if (input->type == HEREDOC)
            *in = change_fd(*in, input->fd); // aqui estou pegando o fd do primeiro e nao do ultimo
        if (*in < 0)
            return ; // nao e prar retornar e sim sair do programa
    }
    if (output)
    {
        *out = change_fd(*out, helper_output(output));
        if (*out < 0)
            return ;
    }
}
