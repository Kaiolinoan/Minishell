/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:42:23 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/27 17:36:19 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_here_doc(char *limiter)
{
	char	*line;
    int     fd;
    pid_t   pid;
    
    fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
        return (-1);
    pid = fork();
    if (pid < 0)
        return (ft_close(&fd), -2);
    if (!pid)
    {
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
    wait(NULL);
    ft_close(&fd);
    fd = open("/tmp/here_temp", O_RDONLY);
	return (fd);
}

static int helper_input(t_redirect *input)
{
    int fd;
    
    if (!input)
		return  -1;
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
		return (-1) ;
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
        *in = change_fd(*in, helper_input(input));
        if (*in < 0)
            return ;
    }
    if (output)
    {
        *out = change_fd(*out, helper_output(output));
        if (*out < 0)
            return ;
    }
}

//nao esta printando aqui dentro, e o append nao funciona
