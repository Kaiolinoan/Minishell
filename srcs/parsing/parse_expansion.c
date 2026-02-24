/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:30:53 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 06:56:39 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	expand_and_shi(t_command *head, t_map *env)
{
	char	**new_args;

	while (head)
	{
		new_args = expand_with_splitting(head->args, env);
		if (!new_args)
			return (0);
		free(head->args);
		head->args = new_args;
		if (!expand_redirects(head->infile, env))
			return (0);
		if (!expand_redirects(head->outfile, env))
			return (0);
		head = head->next;
	}
	return (1);
}
