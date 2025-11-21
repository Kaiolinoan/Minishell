/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:24:01 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/18 16:33:46 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*new_cmdnode(char **args)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->command = args;
	node->infile = NULL;
	node->outfile = NULL;
	node->next = NULL;
	return (node);
}

static t_command	*fill_cmdlist(t_command *head, char *command)
{
	char		**args;
	t_command	*new_node;
	t_command	*current;

	args = ft_split(command, '\2');
	if (!args)
		return (NULL);
	new_node = new_cmdnode(args);
	if (!new_node)
		return (free_grid(args), NULL);
	if (!head)
		head = new_node;
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (head);
}

t_command	*parse_main(char *input, t_command  *head)
{
	size_t	i;
	char	**command;

	input = parse_input(input);
	if (!input)
		return (NULL);
	command = ft_split(input, '\3');
	if (!command)
		return (NULL);
	i = 0;
	while (command[i])
	{
		head = fill_cmdlist(head, command[i]);
		if (!head)
			return (NULL);
		i++;
	}
	free(input);
	free_grid(command);
	return (head);
}