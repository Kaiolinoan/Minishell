/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:16:36 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/23 20:45:54 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map *new_map(void)
{
    t_extra *map;

    map = malloc(sizeof(t_extra));
    if (!map)
        return (NULL);
    map->put = __put;
    map->get = __get;
    map->remove = __remove;
    map->destroy = __destroy;
    map->head = NULL;
    map->tail = NULL;
    map->size = 0;
    return ((t_map *)map);
}

t_envlist *new_node(char *k, char *v)
{
    t_envlist  *node;

    node = malloc(sizeof(t_envlist));
    if (!node)
        return (NULL);
    node->key = k;
    node->value = v;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}
