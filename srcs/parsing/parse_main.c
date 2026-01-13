/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:24:01 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/13 04:08:26 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*new_cmdnode(char **args, t_map *env)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->cmd = args;
	node->args = NULL;
	node->pid = 0;
	node->path = get_path(env, args);
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
	if (!args || !cmds || !cmds[0])
		return (free_grid(cmds), NULL);
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

t_command	*parse_main(char *input, t_command  *head, t_map *env)
{
	size_t	i;
	char	**args;

	input = parse_input(input);
	if (!input)
		return (NULL);
	args = ft_split(input, '\3');
	if (!args)
		return (free(input), NULL);
	i = 0;
	while (args[i])
	{
		head = fill_cmdlist(head, args[i], env);
		if (!head)
			return (free(input), free_grid(args), NULL);
		i++;
	}
	if (!in_redirection(head))
		return (free_all(&head), free_grid(args), free(input), NULL);
	// if (!expand_and_shi(head, env))
	// 	return (free_grid(args), free(input), NULL);
	return (free_grid(args), free(input), head);
}
