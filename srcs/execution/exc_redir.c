/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:42:23 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/25 16:54:55 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int here_doc(char *limiter)
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
            line = get_next_line(0);
            if (!line)
                (free(line), exit(0));
            if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
    			&& (line[ft_strlen(limiter)] == '\n'))
                {
                    free(line);
                    break ;
                }
            ft_putstr_fd(line, fd);
            free(line);
        }
        ft_close(&fd);
        exit(0);
    }
	return (waitpid(pid, NULL, 0), fd);
}

static void helper_input(t_redirect *input)
{
    int fd;
    int temp_fd;

    if (input == NULL)
		return ;
    temp_fd = -1;
    t_redirect *head = input;
	while (head)
	{   
        ft_close(&temp_fd);
		if (head->type == INPUT)
		{
			fd = open(head->filename, O_RDONLY);
			if (fd < 0)
				return ;
            temp_fd = fd;
		}
		else if (head->type == HEREDOC)
        {
            temp_fd = here_doc(head->filename);
            if (temp_fd == -1)
                return (ft_putstr_fd("ERROR: here_doc\n", 2));
        }
		head = head->next;
	}
    (dup2(temp_fd, STDIN_FILENO), ft_close(&temp_fd));
}

static void helper_output(t_redirect *output)
{
    int fd;

    if (output == NULL)
		return ;
    fd = -1;
	while (output)
	{
        ft_close(&fd);
		if (output->type == OUTPUT)
			fd = open(output->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (output->type == OUTPUT_APPEND)
			fd = open(output->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
        {
            ft_putstr_fd("erro ao abrir fd no output\n", 2);
			return ;
        }
		output = output->next;
	}
	dup2(fd, STDOUT_FILENO);
    ft_close(&fd);
}

void check_redir(t_redirect *input, t_redirect *output)
{
	if (!input && !output)
		return ;
    helper_input(input);
	helper_output(output);
	//fazer a verificao depois
}

//nao esta printando aqui dentro, e o append nao funciona
