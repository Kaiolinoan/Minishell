/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:17:07 by kelle             #+#    #+#             */
/*   Updated: 2026/01/13 05:11:08 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*redir_label(t_type type)
{
	if (type == INPUT)
		return ("<");
	if (type == HEREDOC)
		return ("<<");
	if (type == OUTPUT_APPEND)
		return (">>");
	return (">");
}

static void	print_redirs(const char *name, t_redirect *list)
{
	bool	first;

	first = true;
	if (!list)
	{
		printf("%s: none\n", name);
		return ;
	}
	while (list)
	{
		if (first)
			first = false;
		else
			name = "         ";
		printf("%s: %s %s\n", name, redir_label(list->type),
			list->filename ? list->filename : "(null)");
		list = list->next;
	}
}

void	print_commands_debug(t_command *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("cmd[%d]:\n", i);
		printf("  path: %s\n", head->path ? head->path : "(null)");
		if (!head->args || !head->args[0])
			printf("  args: none\n");
		else
		{
			int	j;

			printf("  args:");
			j = 0;
			while (head->args[j])
				printf(" [%s]", head->args[j++]);
			printf("\n");
		}
		print_redirs("  infile", head->infile);
		print_redirs("  outfile", head->outfile);
		head = head->next;
		i++;
	}
}

static void print_cmd_tokens(t_command *node)
{
	int j;

	if (!node->cmd)
	{
		printf("  cmd tokens: none\n");
		return ;
	}
	printf("  cmd tokens:\n");
	j = 0;
	while (node->cmd[j])
	{
		if (node->cmd[j][0] == '\1')
			printf("    [%d]: (masked)\n", j);
		else
			printf("    [%d]: %s\n", j, node->cmd[j]);
		j++;
	}
}

void	print_nodes_after_input(t_command *head)
{
	int i;

	i = 0;
	while (head)
	{
		printf("node[%d]:\n", i);
		printf("  path: %s\n", head->path ? head->path : "(null)");
		print_cmd_tokens(head);
		if (!head->args || !head->args[0])
			printf("  args: none\n");
		else
		{
			int j;

			printf("  args:");
			j = 0;
			while (head->args[j])
				printf(" [%s]", head->args[j++]);
			printf("\n");
		}
		print_redirs("  infile", head->infile);
		print_redirs("  outfile", head->outfile);
		head = head->next;
		i++;
	}
}

