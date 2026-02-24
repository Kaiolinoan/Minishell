/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:32:35 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 06:24:26 by kelle            ###   ########.fr       */
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

static int	fill_args(t_command *current, int i, int j)
{
	int	count;

	count = args_count(current->cmd);
	if (!count)
	{
		current->args = calloc(1, sizeof(char *));
		return (current->args != NULL);
	}
	current->args = calloc(count + 1, sizeof(char *));
	if (!current->args)
		return (0);
	while (current->cmd[i])
	{
		if (current->cmd[i][0] != '\1')
		{
			current->args[j] = ft_strdup(current->cmd[i]);
			if (!current->args[j])
				return (free_grid(current->args), 0);
			j++;
		}
		i++;
	}
	current->args[j] = NULL;
	return (1);
}

static int	process_redirection(t_command *current, int *i, char redir_type)
{
	if (!check_redir_error(current, *i, redir_type))
		return (0);
	if (!current->cmd[*i + 1])
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token");
		return (ft_dprintf(2, " `newline'\n"), 0);
	}
	if (current->cmd[*i + 1][0] == '<' || current->cmd[*i + 1][0] == '>')
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token");
		return (ft_dprintf(2, " `%c'\n",
				current->cmd[*i + 1][0]), 0);
	}
	if (!handle_redirection(current, *i, redir_type))
		return (0);
	*i += 2;
	return (1);
}

static int	search_redirections(t_command *current)
{
	int	i;

	i = 0;
	while (current->cmd[i])
	{
		if (current->cmd[i][0] == '<')
		{
			if (!process_redirection(current, &i, '<'))
				return (0);
			continue ;
		}
		if (current->cmd[i][0] == '>')
		{
			if (!process_redirection(current, &i, '>'))
				return (0);
			continue ;
		}
		i++;
	}
	return (fill_args(current, 0, 0));
}

int	parse_redirection(t_command *head)
{
	t_command	*current;

	current = head;
	while (current)
	{
		if (!search_redirections(current))
			return (0);
		current = current->next;
	}
	return (1);
}
