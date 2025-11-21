/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:13:04 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/21 18:20:32 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initialize_pipes(t_pipe *pipe)
{
	pipe->pipe_fd1[0] = -1;
	pipe->pipe_fd1[1] = -1;
	pipe->pipe_fd2[0] = -1;
	pipe->pipe_fd2[1] = -1;
	pipe->prev = NULL;
	pipe->current = pipe->pipe_fd1;
}

bool create_pipes(t_pipe *p)
{
	if (pipe(p->current) < 0)
		return (false);
	return (true);
}

void switch_pipes(t_pipe *p)
{
	int *temp;

	temp = p->current;
	p->prev = p->current;
	if (temp == p->pipe_fd1)
		p->current = p->pipe_fd2;
	else
		p->current = p->pipe_fd1;
}