/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:42:23 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/15 13:15:20 by klino-an         ###   ########.fr       */
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
				return (perror(input->filename), -1);
		}
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
			return (perror(output->filename), -1);
		output = output->next;
	}
	return (fd);
}

void print_inside_redir(t_redirect *ptr)
{
	t_redirect *temp;

	temp = ptr;
	while (temp)
	{
		printf("filename: %s\n", temp->filename);
		printf("fd: %d\n", temp->fd);
		printf("type: %d\n", temp->type);
		temp = temp->next;
	}
}

int	check_redir(t_redirect *input, t_redirect *output, int *in, int *out)
{
	if (!input && !output)
		return (-2);
	// print_inside_redir(input);
	if (input)
	{
		if (input->type == INPUT)
			*in = change_fd(*in, helper_input(input));
		if (input->type == HEREDOC)
			*in = change_fd(*in, input->fd);// aqui estou pegando o fd do primeiro e nao do ultimo
	}
	if (output)
		*out = change_fd(*out, helper_output(output));
	if (*in < 0 || *out < 0)
		return (-1);
	return (true);
}
