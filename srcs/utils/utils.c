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

void clear_exec(t_exec *exec)
{
	if (!exec)
		return ;
	ft_close(&exec->in);
	ft_close(&exec->out);
	ft_close(&exec->fds[0]);
	ft_close(&exec->fds[1]);
	exec = NULL;
}

void free_all(t_command *commands, t_exec *exec)
{
	t_command			*next;

	if (!commands)
		return ;
	while (commands->prev)
		commands = commands->prev;
	while (commands)
	{
		next = commands->next;
		list_clear_redir(commands->infile);
		list_clear_redir(commands->outfile);
		free(commands->path);
		clear_matriz(commands->args);
		clear_matriz(commands->cmd);
		free(commands);
		commands = next;
	}
	clear_exec(exec);
	commands = NULL;
}

