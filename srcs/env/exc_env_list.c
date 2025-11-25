/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:16:36 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/25 19:33:35 by klino-an         ###   ########.fr       */
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
	map->to_string = __to_string;
	map->destroy = __destroy;
	map->print = __print;
	map->set_var_as_exported = __set_var_as_exported;
	map->head = NULL;
	map->tail = NULL;
	map->size = 0;
	return ((t_map *)map);
}

t_envlist	*new_node(char *k, char *v, bool exported)
{
	t_envlist	*node;

	node = malloc(sizeof(t_envlist));
	if (!node)
		return (NULL);
	node->key = k;
	node->value = v;
	node->exported = exported;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_command	*new_command(char **args)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = args;
	node->next = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	return (node);
}

t_redirect	*new_redirect(char *filename, char type)
{
	t_redirect	*node;

	node = malloc(sizeof(t_redirect));
	if (!node)
		return (NULL);
	node->filename = filename;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_var	*new_var(char *k, char *v, bool exported, bool commands)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->key = k;
	node->value = v;
	node->is_exported = exported;
	node->commands = commands;
	node->next = NULL;
	return (node);
}
