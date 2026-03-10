/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:42:23 by klino-an          #+#    #+#             */
/*   Updated: 2026/03/10 16:19:25 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	helper_input(t_redirect *input)
{
	int	fd;

	if (!input)
		return (-1);
	fd = STDIN_FILENO;
	while (input)
	{
		if (input->type == INPUT)
		{
			fd = open(input->filename, O_RDONLY);
			if (fd < 0)
				return (ft_dprintf(2, "bash: "), perror(input->filename), -1);
		}
		else if (input->type == HEREDOC && input->fd != -1)
			fd = input->fd;
		if (input->next)
			ft_close(&fd);
		input = input->next;
	}
	return (fd);
}

static int	helper_output(t_redirect *output)
{
	int	fd;

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
			return (ft_dprintf(2, "bash: "), perror(output->filename), -1);
		if (output->next)
			ft_close(&fd);
		output = output->next;
	}
	return (fd);
}

int	check_redir(t_redirect *input, t_redirect *output, int *in, int *out)
{
	if (!input && !output)
		return (-2);
	if (input)
		*in = change_fd(*in, helper_input(input));
	if (output)
		*out = change_fd(*out, helper_output(output));
	if (*in < 0 || *out < 0)
		return (-1);
	return (true);
}
