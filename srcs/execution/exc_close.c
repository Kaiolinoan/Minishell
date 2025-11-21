/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:14:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/21 18:17:57 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

void close_all(t_pipe *pipe)
{
	if (pipe->prev)
	{
		ft_close(&pipe->prev[1]);
		ft_close(&pipe->prev[0]);
	}
	if (pipe->current)
	{
		ft_close(&pipe->current[0]);
		ft_close(&pipe->current[1]);
	}
}