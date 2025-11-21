/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/11/05 14:09:48 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/05 14:09:48 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_matriz(char **matriz)
{
	size_t	i;

	i = 0;
	while (matriz[i])
		free(matriz[i++]);
	free(matriz);
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

