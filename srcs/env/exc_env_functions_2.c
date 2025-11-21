/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:12:28 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/18 15:17:04 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__destroy(t_extra *t)
{
	t_envlist	*tmp;

	if (!t)
		return ;
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

void	__print(t_extra *t)
{
	t_envlist	*temp;

	temp = t->head;
	while (temp)
	{
		if (temp->exported)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	__set_var_as_exported(t_extra *t, char *key)
{
	t_envlist	*f;

	f = find(t, key);
	if (f)
		f->exported = true;
	return ;
}

static char	*get_full_str(t_envlist *tmp)
{
	char	*str;

	str = NULL;
	str = ft_strdup(tmp->key);
	if (!str)
		return (NULL);
	str = gnl_strjoin(str, "=");
	if (!str)
		return (free(str), NULL);
	str = gnl_strjoin(str, tmp->value);
	if (!str)
		return (free(str), NULL);
	return (str);
}

char	**__to_string(t_extra *t)
{
	char		**matriz;
	char		*str;
	t_envlist	*tmp;
	size_t		i;

	tmp = t->head;
	matriz = malloc(sizeof(char *) * (list_len_extra(t) + 1));
	if (!matriz)
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (tmp->exported)
		{
			str = get_full_str(tmp);
			if (!str)
				return (clear_matriz(matriz), NULL);
			matriz[i++] = str;
		}
		tmp = tmp->next;
	}
	matriz[i] = NULL;
	return (matriz);
}
