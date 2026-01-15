/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:50:33 by kelle             #+#    #+#             */
/*   Updated: 2025/12/25 05:40:22 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_count(char *str)
{
	int		i;
	char	redirection;

	i = 0;
	redirection = str[0];
	while (str[i])
	{
		if (str[i] == redirection)
			i++;
		else
			return (0);
	}
	return (i > 0 && i <= 2);
}

static t_type	get_redir_type(t_command *node, int i, char flag)
{
	if (flag == '<')
	{
		if (node->cmd[i][1])
			return (HEREDOC);
		return (INPUT);
	}
	if (node->cmd[i][1])
		return (OUTPUT_APPEND);
	return (OUTPUT);
}

static t_redirect	*new_redirect_node(t_command *node, int i, char flag)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = get_redir_type(node, i, flag);
	redir->filename = ft_strdup(node->cmd[i + 1]);
	node->cmd[i][0] = '\1';
	node->cmd[i + 1][0] = '\1';
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

static void	append_redirect(t_redirect **head, t_command *cmdnode,
		int i, char redir)
{
	t_redirect	*node;
	t_redirect	*current;

	node = new_redirect_node(cmdnode, i, redir);
	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = node;
}

int	handle_redirection(t_command *cmdnode, int i, char redir)
{
	if (!redir_count(cmdnode->cmd[i]))
		return (0);
	if (redir == '<')
		append_redirect(&cmdnode->infile, cmdnode, i, '<');
	else
		append_redirect(&cmdnode->outfile, cmdnode, i, '>');
	return (1);
}
