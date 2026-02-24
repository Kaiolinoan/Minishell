/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:24:01 by klino-an          #+#    #+#             */
/*   Updated: 2026/02/15 06:24:26 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*new_cmdnode(char **args)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->cmd = args;
	node->args = NULL;
	node->pid = 0;
	node->path = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static t_command	*fill_cmdlist(t_command *head, char *args)
{
	char		**cmds;
	t_command	*new_node;
	t_command	*current;

	cmds = ft_split(args, '\2');
	if (!cmds || !cmds[0])
		return (free_grid(cmds), NULL);
	new_node = new_cmdnode(cmds);
	if (!new_node)
		return (free_grid(cmds), NULL);
	if (!head)
		head = new_node;
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
	return (head);
}

static t_command	*build_cmdlist(char **args, t_map *env)
{
	size_t		i;
	t_command	*head;

	head = NULL;
	i = 0;
	while (args[i])
	{
		head = fill_cmdlist(head, args[i]);
		if (!head)
		{
			put_exit_code_in_env(env, 2);
			free_grid(args);
			return (NULL);
		}
		i++;
	}
	return (head);
}

static t_command	*finalize_parsing(t_command *head, char **args,
		t_map *env, t_exec *exec)
{
	if (!parse_redirection(head))
	{
		put_exit_code_in_env(env, 2);
		free_all(head, exec);
		free_grid(args);
		return (NULL);
	}
	if (!expand_and_shi(head, env))
	{
		free_grid(args);
		return (NULL);
	}
	free_grid(args);
	return (head);
}

t_command	*parse_main(char *input, t_map *env, t_exec *exec)
{
	char		**args;
	t_command	*head;

	input = parse_input(input);
	if (!input)
		return (put_exit_code_in_env(env, 0), NULL);
	if (!check_pipe_syntax(input))
		return (put_exit_code_in_env(env, 2), free(input), NULL);
	args = ft_split(input, '\3');
	if (!args)
		return (free(input), NULL);
	free(input);
	input = NULL;
	head = build_cmdlist(args, env);
	if (!head)
		return (NULL);
	return (finalize_parsing(head, args, env, exec));
}
