/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:14:33 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/12 15:22:34 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

int	change_fd(int old, int new)
{
	if (old != -1)
		ft_close(&old);
	return (new);
}

void	close_fds(t_exec *exec, t_command *cmd, bool is_parent)
{
	ft_close(&exec->in);
	ft_close(&exec->out);
	ft_close(&exec->fds[1]);
	if (is_parent)
	{
		if (!cmd->next)
			ft_close(&exec->fds[0]);
	}
	else
		ft_close(&exec->fds[0]);
	// ft_close(&cmd->infile->fd);
}
