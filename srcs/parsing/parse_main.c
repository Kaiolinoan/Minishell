/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:24:01 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/30 18:03:12 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*new_cmdnode(char **args, t_map *env)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = args;
	node->pid = 0;
	node->path = get_path(env, args);
	node->exec = new_exec();
	node->infile = NULL;
	node->outfile = NULL;
	node->next = NULL;
	return (node);
}

static t_command	*fill_cmdlist(t_command *head, char *args, t_map *env)
{
	char		**cmds;
	t_command	*new_node;
	t_command	*current;

	cmds = ft_split(args, '\2');
	if (!cmds)
		return (NULL);
	new_node = new_cmdnode(cmds, env);
	if (!new_node)
		return (free_grid(cmds), NULL);
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

t_command	*parse_main(char *input, t_map *env)
{
	size_t		i;
	char		**args;
	t_command	*head;

	head = NULL;
	input = parse_input(input);
	if (!input)
		return (NULL);
	args = ft_split(input, '\3');
	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		head = fill_cmdlist(head, args[i], env);
		if (!head)
			return (NULL);
		i++;
	}
	free(input);
	free_grid(args);
	return (head);
}
