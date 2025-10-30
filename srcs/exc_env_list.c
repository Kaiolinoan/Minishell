/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:16:36 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/29 19:15:54 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*new_map(void)
{
	t_extra	*map;

	map = malloc(sizeof(t_extra));
	if (!map)
		return (NULL);
	map->put = __put;
	map->get = __get;
	map->remove = __remove;
	map->destroy = __destroy;
	map->print = __print;
	map->head = NULL;
	map->tail = NULL;
	map->size = 0;
	return ((t_map *)map);
}

t_envlist	*new_node(char *k, char *v)
{
	t_envlist	*node;

	node = malloc(sizeof(t_envlist));
	if (!node)
		return (NULL);
	node->key = k;
	node->value = v;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_command	*new_command(char **command)
{
	t_command *node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->command = command;
	node->next =  NULL;
	node->infile = NULL;
	node->outfile = NULL;
	return (node);
}

t_redirect  *new_redirect(char *filename, char type)
{
	t_redirect *node;

	node = malloc(sizeof(t_redirect));
	if (!node)
		return (NULL);
	node->filename = filename;
	node->type = type;
	node->next = NULL;
	return (node);
}