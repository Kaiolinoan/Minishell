/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:32:35 by kelle             #+#    #+#             */
/*   Updated: 2026/01/13 03:41:04 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_count(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '\1')
			count++;
		i++;
	}
	return (count);
}

static int	fill_args(t_command *current)
{
	int	i;
	int	j;
	int count;

	count = args_count(current->cmd);
	if (!count)
		return (0);
	current->args = calloc(count + 1, sizeof(char *));
	if (!current->args)
		return (0);
	i = 0;
	j = 0;
	while (current->cmd[i])
	{
		if (current->cmd[i][0] != '\1')
		{
			current->args[j] = ft_strdup(current->cmd[i]);
			if (!current->args[j])
				return(free_grid(current->args), 0);
			j++;	
		}
		i++;
	}
	current->args[j] = NULL;
	return (1);
}

int in_redirection(t_command *head)
{
	int         i;
	t_command   *current;

	current = head;
	while (current)
	{
		i = 0;
		while (current->cmd[i])
		{
			if (current->cmd[i][0] == '<' || current->cmd[i][0] == '>')
			{
				if (!current->cmd[i + 1])
					return (0);
				if (!handle_redirection(current, i, current->cmd[i][0]))
					return (0);
				break ;
			}
			i++;
		}
		if (!fill_args(current))
			return (0);
		current = current->next;
	}
	return (1);
}
