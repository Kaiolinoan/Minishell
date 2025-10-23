/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:12:28 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/23 21:02:09 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void __destroy(t_extra *t)
{
	t_envlist *tmp;

	tmp = t->head;
	while (t->head)
	{
		tmp = t->head->next;
		free(t->head->key);
		free(t->head->value);
		free(t->head);
		t->head = tmp;
	}
	free(t);
}

char	**ft_split_env(char *env)
{
	static char *args[2];
	char *start;

	args[1] = NULL;
	start = ft_strchr(env, '=');
	if (start)
	{
		args[1] = ft_strdup(start + 1);
		*start = '\0';
	}
	args[0] = ft_strdup(env);
	printf("%s=%s\n", args[0], args[1]);
	return (args);
}

void create_env(t_map *env, char **enviroment)
{
	size_t		i;
	char 		**args;

	i = 0;
	while (enviroment[i])
	{
		args = ft_split_env(enviroment[i]);
		env->put(env, args[0], args[1]);
		i++;
	}
}

int main(int argc, char **argv, char **enviroment)
{
	t_map *env;

	(void)argc;
	(void)argv;
	env = new_map();
	create_env(env, enviroment);
	env->destroy(env);
}
