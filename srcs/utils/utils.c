/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:25:44 by kelle             #+#    #+#             */
/*   Updated: 2026/01/13 00:25:44 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_matriz(char **matriz)
{
	size_t	i;

	if (!matriz)
		return ;
	i = 0;
	while (matriz[i])
		free(matriz[i++]);
	free(matriz);
	matriz = NULL;
}

size_t	list_len_command(t_command *commands)
{
	size_t		count;
	t_command	*temp;

	temp = commands;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

size_t	list_len_extra(t_extra *env)
{
	size_t		count;
	t_envlist	*temp;

	temp = env->head;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// void	create_variable(t_map *env, t_var *var)
// {
// 	env->put(env, var->key, var->value, var->is_exported);
// }

void	sort_str(char **matriz)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (matriz[i])
	{
		j = i + 1;
		while (matriz[j])
		{
			if (ft_strcmp(matriz[i], matriz[j]) > 0)
			{
				tmp = matriz[i];
				matriz[i] = matriz[j];
				matriz[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void free_all(t_command **commands)
{
	t_command			*next;
	t_command			*current;

	if (!commands || !*commands)
		return ;
	current = *commands;
	while (current)
	{
		next = current->next;
		list_clear_redir(current->infile);
		list_clear_redir(current->outfile);
		if (current->path)
			free(current->path);
		clear_matriz(current->cmd);
		clear_matriz(current->args);
		free(current);
		current = next;
	}
	*commands = NULL;
}

