/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:42:23 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/21 20:06:45 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int here_doc(t_redirect *input, t_pipe *p)
{
    char	*limiter;
	char	*line;
    int     fd;
    pid_t   pid;
    
	line = NULL;
	limiter = input->filename;
    fd = open("/tmp/here_temp", O_WRONLY | O_CREAT | O_TRUNC | 0600);
    if (fd < 0)
        return (-1);
    pid = fork();
    if (pid < 0)
        return (-1);
    if (!pid)
    {
        while (1)
        {
            line = get_next_line(0);
            if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
    			&& (line[ft_strlen(limiter)] == '\n'))
                {
                    free(line);
                    break ;
                }
            ft_putstr_fd(line, fd);
            free(line);
        }
    }
	return (ft_close(&fd), fd);
}

static void helper_input(t_redirect *input, t_pipe *pipe)
{
    int fd;
    int temp_fd;
    int heredoc_fd;
    (void) pipe;

    if (input != NULL)
	{
		while (input)
		{
			if (input->type == INPUT)
			{
				fd = open(input->filename, O_RDONLY);
				if (fd < 0)
					return ;
                temp_fd = fd;
			}
			else if (input->type == HEREDOC)
            {
                heredoc_fd = here_doc(input, pipe);
                if (heredoc_fd == -1)
                    return ((void)printf("ERROR: here_doc"));
                temp_fd = heredoc_fd;
            }
			input = input->next;
		}
        dup2(temp_fd, STDIN_FILENO);
	}
}

static void helper_output(t_redirect *output)
{
    int fd;

    if (output != NULL)
	{
		while (output)
		{
			if (output->type == OUTPUT)
				fd = open(output->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (output->type == OUTPUT_APPEND)
				fd = open(output->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return ;
			output = output->next;
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void check_redir(t_redirect *input, t_redirect *output, t_pipe *pipe)
{
	if (input == NULL && output == NULL)
		return ;
    helper_input(input, pipe);
	helper_output(output);
}
