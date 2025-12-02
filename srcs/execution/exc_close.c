/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:14:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/02 16:44:53 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

int change_fd(int old, int new)
{
	return (close(old), new);
}
