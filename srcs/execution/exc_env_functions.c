/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:12:28 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/07 12:51:08 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*find(t_extra *t, char *key)
{
	t_envlist	*head;

	if (!key || !t)
		return (NULL);
	head = t->head;
	while (head)
	{
		if (ft_strlen(head->key) == ft_strlen(key) && (!ft_strncmp(key,
					head->key, ft_strlen(key))))
			return (head);
		head = head->next;
	}
	return (NULL);
}

char	*__get(t_extra *t, char *k)
{
	t_envlist	*node;

	if (!k || !t)
		return (NULL);
	node = find(t, k);
	if (!node)
		return (NULL);
	return (node->value);
}

void	__remove(t_extra *t, char *k)
{
	t_envlist	*node;

	if (!k || !t)
		return ;
	node = find(t, k);
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		t->head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	else
		t->tail = node->prev;
	free(node->key);
	free(node->value);
	free(node);
	t->size--;
}

void	__put(t_extra *t, char *k, char *v, bool exported)
{
	t_envlist	*f;
	t_envlist	*node;

	if (!k || !v || !t)
		return ;
	f = find(t, k);
	if (f)
	{
		free(f->value);
		f->value = v;
		return (free(k));
	}
	node = new_node(k, v, exported);
	if (!node)
		return (free(k), free(v));
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
