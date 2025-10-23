/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:12:28 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/23 15:12:48 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_envlist *find(t_extra *t, char * key)
{
    t_envlist *head;

    head = t->head;
    while (head)
    {
        if (!ft_strncmp(key, head->key, ft_strlen(key)))
            return (head);
        head = head->next;
    }
    return (NULL);
}

char *__get(t_extra *t, char *k)
{
    t_envlist *node;

    node = find(t, k);
    if (!node)
        return (NULL);
    return (node->value);
}

void __remove(t_extra  *t, char *k)
{
    t_envlist *node;

    node = find(t, k);
    if (!node)
        return ;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    t->size--;
}

void __put(t_extra *t, char *k, char *v)
{
    t_envlist *f;
    t_envlist *node;

    if (!k || !v)
        return;
    
    f = find(t, k);
    if (f)
    {
        f->value = v;
        return ;
    }
    node = new_node(k, v);
    if (t->head == NULL)
        t->head = node;
    else 
    {
        t->tail->next = node;
        node->prev = t->tail;
    }
    t->size++;    
    t->tail = node;
}

t_map *new_map(void)
{
    t_extra *map;

    map = malloc(sizeof(t_extra));
    if (!map)
        return (NULL);
    map->put = __put;
    map->get = __get;
    map->remove = __remove;
    return ((t_map *)map);
}

int main()
{
    t_map *j;
    t_map *k;

    j = new_map();
    k = new_map();

    k->put(k, "Poop", "No KILL");
    j->put(j, "ArTY", "yoru 1 trick");
    printf("%s", j->get(j, "ArTY"));
    printf("\n");
    printf("%s", k->get(k, "Poop"));
}