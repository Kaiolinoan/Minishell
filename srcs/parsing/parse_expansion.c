/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:30:53 by kelle             #+#    #+#             */
/*   Updated: 2026/01/22 04:24:15 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(str) + 1, 1);
	if (!result)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (quote && quote == str[i])
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static int	expand_redirects(t_redirect *redir, t_map *env)
{
	char	*new_name;

	while (redir)
	{
		if (redir->type != HEREDOC && redir->filename)
		{
			new_name = expand(redir->filename, env);
			if (!new_name)
				return (0);
			redir->filename = new_name;
		}
		redir = redir->next;
	}
	return (1);
}

static int	expand_args(char **args, t_map *env)
{
	int		i;
	char	*new;

	i = 0;
	while (args[i])
	{
		new = expand(args[i], env);
		if (!new)
			return (0);
		args[i] = new;
		i++;
	}
	return (1);
}

int	expand_and_shi(t_command *head, t_map *env)
{
	t_command	*current;

	current = head;
	while (current)
	{
		if (!expand_args(current->args, env))
			return (0);
		if (!expand_redirects(current->infile, env))
			return (0);
		if (!expand_redirects(current->outfile, env))
			return (0);
		current = current->next;
	}
	return (1);
}
